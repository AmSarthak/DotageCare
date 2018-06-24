#include <LiquidCrystal.h>
#include <Servo.h>
#include <WiFi.h>
char ssid[] = "energia";
char password[] = "supersecret";
LiquidCrystal lcd(2,4,5,6,7,8);
Servo servo_lid;
WiFiServer server(80);

void printWifiStatus() 
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

printWifiStatus();

void setup() 
{
  servo_lid.attach(17);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(15,OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("   Welcome to  ");
  lcd.setCursor(0,1);
  lcd.print("  DOTAGE  CARE ");
  analogWrite(9,140);
}

void loop()
{
   digitalWrite(11,LOW);
   digitalWrite(19,LOW);
   int i = 0;
   WiFiClient client = server.available();   

   IPAddress ip = WiFi.localIP();
   Serial.print("IP Address: ");
   Serial.println(ip);

  if (client)
  {                           
    Serial.println("new client");           
    char buffer[150] = {0};                
    while (client.connected())
    {           
      if (client.available()) 
      {            
        char c = client.read();            
        Serial.write(c);                  
        if (c == '\n') 
        {                    
          if (strlen(buffer) == 0) 
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html><head><title>Energia CC3200 WiFi Web Server</title></head><body align=center>");
            client.println("<h1 align=center><font color=\"red\">Welcome to the CC3200 WiFi Web Server</font></h1>");
            client.print("RED LED <button onclick=\"location.href='/H'\">HIGH</button>");
            client.println(" <button onclick=\"location.href='/L'\">LOW</button><br>");

  
            client.println();
         
            break;
          }
          else 
          {    
            memset(buffer, 0, 150);
            i = 0;
          }
        }
        else if (c != '\r') 
        {    
          buffer[i++] = c;      
        }

        if (endsWith(buffer, "GET /H")) 
        {
          digitalWrite(RED_LED, HIGH);             
        }
        if (endsWith(buffer, "GET /L")) 
        {
          digitalWrite(RED_LED, LOW);           
        }
      }
    }
    client.stop();
    Serial.println("client disonnected");
  }
  
   delay(5000);
   lcd.clear();
   delay(1000);
   lcd.setCursor(0,0);
   lcd.println("Please open link");
   delay(3000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.println(ip);
   delay(1000);
   lcd.setCursor(0,0);
   lcd.println(ip);
   for (int positionCounter = 0; positionCounter < 13; positionCounter++) 
   {
    lcd.scrollDisplayLeft(); 
    delay(300);
   }
   for (int positionCounter = 0; positionCounter < 12; positionCounter++) 
   {
    lcd.scrollDisplayRight(); 
    delay(300);
   }
   delay(5000);
   /*
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.println("Client Connected");
   digitalWrite(11,1);
   delay(5000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("   Welcome to  ");
   lcd.setCursor(0,1);
   lcd.print("  DOTAGE  CARE ");
   delay(5000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Time: 12:30 PM  ");
   lcd.setCursor(0,1);
   lcd.print("  XYZAL M TAB  ");
   digitalWrite(19,HIGH);
   digitalWrite(15,HIGH);
   delay(2000);
   digitalWrite(15,LOW);
   */
   for(int angle = 0; angle <90 ; angle++)
   {
    servo_lid.write(angle);
    delay(50);
   }
   delay(5000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("  Closing Lid   ");
   for(int angle = 90; angle>0 ; angle--)
   {
    servo_lid.write(angle);
    delay(50);
   }
   delay(2000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("   Welcome to  ");
   lcd.setCursor(0,1);
   lcd.print("  DOTAGE  CARE ");
   delay(5000);
   */
}
