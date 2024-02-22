#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include "secrets.h"

#define NOMINATIM_URL "https://nominatim.openstreetmap.org/reverse?format=jsonv2"
#define OVERPASS_URL "http://overpass-api.de/api/interpreter"
#define OVERPASS_QUERY1 "[out:json][maxsize:20000]; way[highway][highway!~\"(footway|track|cycleway|steps|pedestrian|construction)\"][access!~\"(no|private)\"]("
#define OVERPASS_QUERY2 "); out;"
#define BBOX_L 20
#define DOCSIZE 8192
#define GPS_DEBUG

enum Request {
  POST,
  GET
};

HardwareSerial GPSSerial(1);

#define MSPSerial Serial2
#define PCSerial Serial
#define RATE 9600

TinyGPSPlus gps;
HTTPClient** http_nom;
HTTPClient** http_op;
#ifdef GPS_DEBUG
float db_lat, db_lon;
int db_speed;
String cmd;
#endif

void setup() {
#ifdef PCSerial
  PCSerial.begin(115200);
#endif
  GPSSerial.begin(9600, SERIAL_8N1, 27, 26);
  MSPSerial.begin(115200);

  delay(2000);

  WiFi.mode(WIFI_STA);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
#ifdef PCSerial
  PCSerial.print("==> Connecting to WiFi");
#endif
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
#ifdef PCSerial
    PCSerial.print(".");
#endif
    if(WiFi.status() == WL_CONNECTED) {
#ifdef PCSerial
      PCSerial.println();
      PCSerial.println("==> Connected to WiFi");
      PCSerial.println(WiFi.localIP());
#endif
      break;
    }
    if(i > 10) {
#ifdef PCSerial
      PCSerial.println();
      PCSerial.println("==> Cannot connect to WiFi");
#endif
      break;
    }
    i++;
  }

  http_nom = new HTTPClient*;
  http_op = new HTTPClient*;
  *http_nom = new HTTPClient;
  *http_op = new HTTPClient;
  
#ifdef GPS_DEBUG
  db_lat = 46.06477;
  db_lon = 11.14300;
  db_speed = 50;
  PCSerial.println("==> Enabled GPS Debug <==");
#endif
}

void loop() {
  // Update GPS data
  while (GPSSerial.available() > 0) {
    gps.encode(GPSSerial.read());
//    Serial.println("Received data from gps");
  }

#ifdef GPS_DEBUG
  if(PCSerial.available()) {
    char r = PCSerial.read();
    PCSerial.print("==> Received GPS debug command: ");
    PCSerial.println(r);
    switch(r) {
      case 'o':
        cmd = PCSerial.readStringUntil('\n');
        if(cmd != NULL) {
          db_lon = cmd.toFloat();
        }
        break;
      case 'a':
        cmd = PCSerial.readStringUntil('\n');
        if(cmd != NULL) {
          db_lat = cmd.toFloat();
        }
        break;
      case 's':
        cmd = PCSerial.readStringUntil('\n');
        if(cmd != NULL) {
          db_speed = cmd.toInt();
        }
        break;
    }
    PCSerial.println("==> New debug values:\n  Latitude: ");
    PCSerial.println(db_lat);
    PCSerial.print("  Longitude: ");
    PCSerial.println(db_lon);
    PCSerial.print("  Speed: ");
    PCSerial.println(db_speed);
    PCSerial.println("==>");
  }
#endif

  while(MSPSerial.available()) {
    char c = MSPSerial.read();
#ifdef PCSerial
    PCSerial.print("==> Received request: ");
    PCSerial.println(c);
#endif
    String output = requestDispatcher(c);
    
    MSPSerial.print(c);
    MSPSerial.print(output);
    MSPSerial.print('\n');
#ifdef PCSerial
    PCSerial.print("==> Sent to msp: ");
    PCSerial.println(output);
#endif
  }

  delay(10);
}

String requestDispatcher(char c) {
#ifndef GPS_DEBUG
  if(gps.satellites.value() == 0) {
#ifdef PCSerial
    PCSerial.println("==> No GPS fix, returning N/A");
#endif // PCSerial
    return String("?");
  }
#endif // GPS_DEBUG
  if((c == '0' || c == '2') && WiFi.status() != WL_CONNECTED) {
#ifdef PCSerial
    PCSerial.println("==> No WiFi connection, returning N/A");
#endif // PCSerial
    return String("?");
  }

  float lat, lon;
  int spd;
#ifdef GPS_DEBUG
  lat = db_lat;
  lon = db_lon;
  spd = db_speed;
#else
  lat = gps.location.lat();
  lon = gps.location.lng();
  spd = (int)gps.speed.kmph();
#endif
  switch (c){
    case '0': // position
      return getAddress(lat, lon);
    case '1': // speed
      return String(spd);
    case '2': // limit
//      return getRoadLimit(gps.location.lat(), gps.location.lng());
      return getRoadLimit(lat, lon);
    case '3': // lat
      return String(lat, 6);
    case '4': // lon
      return String(lon, 6);
  }
  return String("err");
}

String jsonRequest(Request method, HTTPClient **http_p, String url, String query = "") {
  HTTPClient *http = *http_p;
  if(!http->connected()){
    delete *http_p;
    *http_p = new HTTPClient;
    http = *http_p;
  }
  http->begin(url);

//  Serial.print("==> Sending request to: ");
//  Serial.println(url);

  // Get HTTP response code
  int code;
  if (method == GET) {
    code = http->GET();
  } else if (method == POST) {
    code = http->POST(query);
  }
  if (code > 0) {
    // Successful 

    // Parse JSON response
    String res = http->getString();
    return res;
  } else {
    return String("{\"error\":\"http_error\"}");
  }
}

String getRoadLimit(float latc, float lonc) {
  DynamicJsonDocument doc(DOCSIZE);
  float lat1, lat2, lon1, lon2;
  float delta = (float)BBOX_L / 111111 / 2;
#ifdef PCSerial
  PCSerial.print("==> Delta: ");
  PCSerial.println(String(delta, 6));
#endif
  lat1 = latc - delta;
  lat2 = latc + delta;
  lon1 = lonc - delta;
  lon2 = lonc + delta;
  String post_query = String(OVERPASS_QUERY1) + String(lat1, 7) + "," + String(lon1, 7) + "," + String(lat2, 7) + "," + String(lon2, 7) + OVERPASS_QUERY2;
#ifdef PCSerial
  PCSerial.print("==> Overpass query: ");
  PCSerial.println(post_query);
#endif
  DeserializationError error = deserializeJson(doc, jsonRequest(
    POST,
    http_op,
    String(OVERPASS_URL),
    post_query
  ));
  
  
  if(error) {
    return String("E");
  } else {
    JsonArray elements = doc["elements"];
    if(elements.size() == 0) {
      return String("N");
    }
    int max_speed = 0;
    String type;
    for(JsonObject v: elements) {
      JsonObject tags = v["tags"];
      if(tags.containsKey("maxspeed")) {
        return tags["maxspeed"];
      } else if(tags.containsKey("highway")) {
        return String(defaultRoadLimit(tags["highway"].as<String>()));
      }
    }
    return String(50);
  }
}

String getAddress(float lat, float lon) {
  DynamicJsonDocument doc(DOCSIZE);
  DeserializationError error = deserializeJson(doc, jsonRequest(
    GET,
    http_nom,
    String(String(NOMINATIM_URL) + "&lat=" + String(lat, 6) + "&lon=" + String(lon, 6))
  ));
  
  if(error) {
    return String("!! Can't get address !!");
  } else {
    JsonObject address_info = doc["address"];

    String output = String(
      address_info["road"].as<String>() + ", " +
      address_info["village"].as<String>() + ", " +
      address_info["city"].as<String>() + ", " +
      address_info["country"].as<String>()
    );
    return output;
  }
}

int defaultRoadLimit(String road_type) {
  int limit = 50;
  if(road_type == "motorway") {
    limit = 130;
  } else if(road_type == "trunk") {
    limit = 110;
  } else if(road_type == "primary" || road_type == "secondary" || road_type == "tertiary") {
    limit = 50;
  }
  return limit;
}
