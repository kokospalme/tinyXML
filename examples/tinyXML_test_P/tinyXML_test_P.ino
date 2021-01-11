#include <inttypes.h>
#include <TinyXML.h>
#include <avr/pgmspace.h>
// test data in PROGMEM

TinyXML xml;
uint8_t buffer[100];
uint16_t buflen = 100;

const char PROGMEM message[] = "<?xml version=1.0 encoding=UTF-8?>\
<breakfast_menu>\
<food>\
    <name>Belgian Waffles</name>\
    <price>$5.95</price>\
    <description>\
   Two of our famous Belgian Waffles with plenty of real maple syrup\
   </description>\
    <calories>650</calories>\
</food>\
<food>\
    <name>Homestyle Breakfast</name>\
    <price>$6.95</price>\
    <description>\
    Two eggs, bacon or sausage, toast, and our ever-popular hash browns\
    </description>\
    <calories>950</calories>\
</food>\
<food>\
    <name>French Toast</name>\
    <price>$4.50</price>\
    <description>\
    Thick slices made from our homemade sourdough bread\
    </description>\
    <calories>600</calories>\
</food>\
</breakfast_menu>";

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  xml.init((uint8_t*)&buffer, buflen, &XML_callback);
  Serial.println("Start test");
}

void loop()
{
  char c;
  int index = 0;
  while ( (c = pgm_read_byte_near(message + index)) != 0) {
    xml.processChar(c);
    index++;
  }

  Serial.println("Test done");
  while (1);

}

void XML_callback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen )
{
  if (statusflags & STATUS_START_TAG)
  {
    if ( tagNameLen )
    {
      Serial.print("Start tag ");
      Serial.println(tagName);
    }
  }
  else if  (statusflags & STATUS_END_TAG)
  {
    Serial.print("End tag ");
    Serial.println(tagName);
  }
  else if  (statusflags & STATUS_TAG_TEXT)
  {
    Serial.print("Tag:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
  }
  else if  (statusflags & STATUS_ATTR_TEXT)
  {
    Serial.print("Attribute:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
  }
  else if  (statusflags & STATUS_ERROR)
  {
    Serial.print("XML Parsing error  Tag:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
  }
}
