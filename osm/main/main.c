#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <TinyGPS++.h>

const char* ssid = "REPLACE_SSID";
const char* password = "REPLACE_PASSWORD";

//Your Domain name with URL path or IP address with path
// const char* serverName = "http://192.168.1.106:1880/get-sensor";

// see : "https://nominatim.openstreetmap.org/reverse?format=jsonv2&lat=-34.44076&lon=-58.70521";
const char* exampleQuery = "https://nominatim.openstreetmap.org/reverse?format=jsonv2";


#define GPS_SERIAL Serial2  
#define RATE 9600

//0 Indirizzo, 1 Velocità, 2 Limite Velocità, 3 Lat, 4 Lon

// Define TinyGPS++ object
TinyGPSPlus gps;

void setup() 
{
  // Start serial 
  Serial.begin(115200);
  GPS_SERIAL.begin(RATE);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() 
{
  // Update GPS data
  while (GPS_SERIAL.available() > 0 && WiFi.status() == WL_CONNECTED) 
  {
    if (gps.encode(GPS_SERIAL.read())) 
    {
      // If new data, send req  (geocoding request)
      String response = sendReq(gps.location.lat(), gps.location.lng());

      if(response != "")
      {
        JSONVar jsonRes = parseResponse(response);
        
        printKeys(jsonRes);
      }
    }
  }
}

String sendReq(float lat, float lon) 
{
  // Create HTTP client instance
  HTTPClient http;

  // Build  URL
  String url = String(exampleQuery, sizeof(exampleQuery)) + "&lat=" + String(lat, 6) + "&lon=" + String(lon, 6);
  String payload = "";

  // Start the HTTP request
  http.begin(url);

  Serial.print("Sending request to: ");
  Serial.println(url);

  // Get HTTP response code
  int code = http.GET();
  if (code > 0) 
  {
    // Successful 
    Serial.print("HTTP Response code: ");
    Serial.println(code);

    // Parse JSON response
    payload = http.getString();
    Serial.println("JSON Response:");
    Serial.println(payload);
  } else 
  {
    // Failed to get response
    Serial.print("Request failed. Error code: ");
    Serial.println(code);
  }

  // Close connection
  http.end();

  return payload;
}


JSONVar parseResponse(String payload)
{
  // Create var
  JSONVar jsonRes = JSON.parse(payload);

  // Check parsing
  if (JSON.typeof(jsonRes) == "undefined") 
  {
    Serial.println("Parsing failed!");
    return jsonRes;
  }

  // debug
  Serial.print("JSON object = ");
  Serial.println(jsonRes);

  return jsonRes;
}

String sendAddress(JSONVar jsonRes)
{
  String address = jsonRes["address"];
  return "0" + address;
}

String sendSpeed(JSONVar jsonRes)
{
   // TODO
  // return "1" + // 
}

String sendLimit(JSONVar jsonRes)
{
  int limit = 50;
  String type = jsonRes["highway"];
  switch (type){
    case "motorway": limit = 130;
    break;
    case "primary": limit = 110;
    break;
    // case "motorway": limit = 130;
    // break;
    // case "motorway": limit = 130;
    // break;
    default: limit = 30;
  }
  return "2" +  (String) limit
}

String sendLat(float lat)
{
  return "3" + (String) lat;
}

String sendLat(float lon)
{
  return "4" + (String) lon;
}


void printKeys(JSONVar res)
{
  JSONVar keys = res.keys();
    
  for (int i = 0; i < keys.length(); ++i) 
  {
    JSONVar value = res[keys[i]];
    Serial.print(keys[i]);
    Serial.print(" = ");
    Serial.println(value);
  }
}


