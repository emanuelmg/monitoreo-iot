/*
    ESP8266 NodeMCU NTP (Network Time Protocol) Example
    Hardware: NodeMCU
    Date: 2018
    https://circuits4you.com
*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//const char *ssid = "ARRIS-CA02";
//const char *pass = "A434F4CA8BC88C56";
const char *ssid = "LIAPEP_PRO";
const char *pass = "powerlab";

char HH = -7;
char MM = 00;

const int muestra_min = 10;

unsigned int localPort = 2390;      // local port to listen for UDP packets

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

IPAddress timeServerIP; // time.nist.gov NTP server address

const char* ntpServerName = "1.north-america.pool.ntp.org";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

//=======================================================================
//                     SETUP
//=======================================================================
void setup()
{
  pinMode(12, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while(!Serial) { }
  
  Serial.println("I'm awake.");


  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}

//=======================================================================
//  send an NTP request to the time server at the given address
//=======================================================================
unsigned long sendNTPpacket(IPAddress& address)
{
  //Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

//=======================================================================
//                        LOOP
//=======================================================================
void loop()
{
  char hours, minutes, seconds, minutos;
  digitalWrite(12, HIGH);
  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP); 

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("no packet yet");
  }
  else {
    //Serial.print("packet received, length=");
    //Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    //Serial.print("Seconds since Jan 1 1900 = " );
    //Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    //Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    //Serial.println(epoch);


    // print the hour, minute and second:
    minutes = ((epoch % 3600) / 60);
    minutes = minutes + MM; //Add UTC Time Zone
    
    hours = (epoch  % 86400L) / 3600;   
    //Serial.println(hours,DEC);
    if(hours < 7)
    {
      hours = hours + 24;
    
      if(minutes > 59)
      {  
            
        hours = hours + HH + 1; //Add UTC Time Zone  
        minutes = minutes - 60;
        
        
      }
      else
      {
        hours = hours + HH;
      }
    }
    else
     {
      if(minutes > 59)
      {  
            
        hours = hours + HH + 1; //Add UTC Time Zone  
        minutes = minutes - 60;
        
        
      }
      else
      {
        hours = hours + HH;
      } 
     }
    
    //Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    if ( hours < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }    
    Serial.print(hours,DEC); // print the hour (86400 equals secs per day)
    Serial.print(':');
    

    if ( minutes < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }    
    Serial.print(minutes,DEC); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    
    seconds = (epoch % 60);
    if ( seconds < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(seconds,DEC); // print the second
  
  // wait ten seconds before asking for the time again
  //Serial.println(minutes);
  //String minstr = String(minstr + minutes);
  //int minutos =minstr.toInt();
  //Serial.println(minutes,DEC);
  
  if(((minutes % muestra_min) == 0))
  {
    Serial.println("Me dormiré por 10 min");
    digitalWrite(12, LOW);
    ESP.deepSleep(540e6);
  }
  else if(((minutes % muestra_min) != 0) && (minutes != 9))
  {
      if(minutes <= 10)
      {
        minutes = 9 - minutes;
         
      }
      else if((minutes < 20) && (minutes > 10))
      {
         minutes = 19 - minutes;
      }
      else if((minutes < 30) && (minutes > 20))
      {
        minutes = 29 - minutes;
      }
      else if((minutes < 40) && (minutes > 30))
      {
        minutes = 39 - minutes;
      }
      else if((minutes < 50) && (minutes > 40))
      {
        minutes = 49 - minutes;
      }
      else if((minutes < 60) && (minutes > 50))
      {
        minutes = 59 - minutes;
      }

      if(minutes == 0)
       {
         Serial.println("Me dormiré por 10 min");
         digitalWrite(12, LOW);
         ESP.deepSleep(540e6);  
       }
       else
       {
       //Serial.println(minutes, DEC);
       int minutos = int(minutes);
       int minutoseg = minutos * 60 * 1e6;
       //Serial.println(minutoseg);
       Serial.print("Going into deep sleep for: ");
       Serial.print(minutos);
       Serial.println(" min");
       digitalWrite(12, LOW);
       ESP.deepSleep(minutoseg);
       }
   }
   else if(minutes == 9)
   {
    Serial.println("Me dormiré por 10 min");
    digitalWrite(12, LOW);
    ESP.deepSleep(540e6);
    } 
      

  }
  
  //delay(2000);
}
//=======================================================================
