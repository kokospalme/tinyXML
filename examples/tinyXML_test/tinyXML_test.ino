// parse simple xml message
#include <inttypes.h>
#include <TinyXML.h>

TinyXML xml;
uint8_t buffer[100];
uint16_t buflen = 100;
char message[] = "<obj_1><environment>Earth</environment><data><value1>5</value1><value2>11</value2></data></obj_1>";

void setup()
{
  Serial.begin(9600);
  xml.init((uint8_t*)&buffer, buflen, &XML_callback);
  Serial.println("Start test");
  delay(500);
}

void loop()
{
  char *c = message;
  do {
    xml.processChar(*c);
  }  while (*c++);

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
