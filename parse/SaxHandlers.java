import org.xml.sax.*;

public class SaxHandlers implements ContentHandler {
    public void startDocument() 
    {
	return;
    }

    public void endDocument()
    {
	return;
    }
      
    public void startElement(String name, String localName, String qName, Attributes attrs)
    {
	return;
    }

    public void endElement(String name, String localName, String qName)
    {
	return;
    }

    public void characters(char[] cbuf, int start, int len) 
    {
	return;
    }

    public void endPrefixMapping(String prefix) {
	return;
    }
    
    public void ignorableWhitespace(char[] ch, int start, int length) {
	return;
    }
    
    public void processingInstruction(String target, String data) {
	return;
    }

    public void setDocumentLocator(Locator locator) {
	return;
    }
    
    public void skippedEntity(String name) {
	return;
    }

    public void startPrefixMapping(String prefix, String uri) {
	return;
    }
}
