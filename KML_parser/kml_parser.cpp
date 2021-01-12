#include <inttypes.h>
#include <stdio.h>

#include "TinyXML.cpp"

TinyXML xml;

uint8_t buffer[100];
uint16_t buflen = 100;
char filename[] = "kml.txt"; //input file name

void XML_callback( uint8_t statusflags, char* tagName,  uint16_t tagNameLen,  char* data,  uint16_t dataLen )
{

  if  (statusflags & STATUS_TAG_TEXT)
  {
/*   Serial.print("Tag:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
    */
    printf("Tag: %s text: %s\n",tagName, data);
  }
  else if  (statusflags & STATUS_ATTR_TEXT)
  {
/*    Serial.print("Attribute:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
*/
  printf("Attribute: %s text %s\n",tagName, data);
  }
  else if  (statusflags & STATUS_ERROR)
  {
/*    Serial.print("XML Parsing error  Tag:");
    Serial.print(tagName);
    Serial.print(" text:");
    Serial.println(data);
*/
  printf("XML parsing error Tag: %s text: %s\n",tagName, data);
  }
}


int main()
{
  xml.init(buffer, buflen, &XML_callback);
//  Serial.println("Start test");
  printf("Start test\n");

  FILE * fpin, * fpout;
   fpin = fopen (filename, "r");
   if (fpin == NULL) {
    printf("input file open failure %d\n",errno);
   }
//   fpout = fopen("junk.dat","w");
    int nchar=0;
    int c;
    do {
      c = fgetc (fpin);
      nchar++;
      xml.processChar( (uint8_t) c);
    } while (c != EOF);
    printf("Done. %d characters processed\n",nchar);
    while(1); //hang
    return 0;
}
