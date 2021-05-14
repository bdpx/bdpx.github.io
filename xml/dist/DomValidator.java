/*
 * (C) Copyright IBM Corp. 2004.  All rights reserved.
 *
 * US Government Users Restricted Rights Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * The program is provided "as is" without any warranty express or
 * implied, including the warranty of non-infringement and the implied
 * warranties of merchantibility and fitness for a particular purpose.
 * IBM will not be liable for any damages suffered by you as a result
 * of using the Program. In no event will IBM be liable for any
 * special, indirect or consequential damages or lost profits even if
 * IBM has been advised of the possibility of their occurrence. IBM
 * will not be liable for any third party claims against you.
 */

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

/**
 * A sample DOM writer. This sample program illustrates how to
 * traverse a DOM tree.
 */

public class DomValidator
  extends DefaultHandler
{
  private boolean documentIsValid = true;
  private boolean documentHadWarnings = false;

  public void parseAndValidate(String uri, boolean useSchema)
  {
    Document doc = null;

    try
    {
      DocumentBuilderFactory dbf = 
        DocumentBuilderFactory.newInstance();
      dbf.setNamespaceAware(true);
      dbf.setValidating(true);
      if (useSchema)
          dbf.setAttribute("http://java.sun.com/xml/jaxp/properties/schemaLanguage", 
                           "http://www.w3.org/2001/XMLSchema");
      DocumentBuilder db = dbf.newDocumentBuilder();
      db.setErrorHandler(this);
      doc = db.parse(uri);

      if (documentIsValid)
        System.out.println("\nYour document is valid!");
      else if (documentHadWarnings)
        System.out.println("\nYour document had minor errors (warnings).");
      else
        System.out.println("\nYour document is not valid.");
    }
    catch (Exception e)
    {
      System.err.println("Sorry, an error occurred: " + e);
    }
  }

  /** Warning. */
  public void warning(SAXParseException ex) 
  {
    documentHadWarnings = true;
    documentIsValid = false;
    System.err.println("[Warning] "+
                       getLocationString(ex)+": "+
                       ex.getMessage());
  }

  /** Error. */
  public void error(SAXParseException ex) 
  {
    documentIsValid = false;
    System.err.println("[Error] "+
                       getLocationString(ex)+": "+
                       ex.getMessage());
  }

  /** Fatal error. */
  public void fatalError(SAXParseException ex) 
    throws SAXException 
  {
    documentIsValid = false;
    System.err.println("[Fatal Error] "+
                       getLocationString(ex)+": "+
                       ex.getMessage());
    throw ex;
  }

  /** Returns a string of the location. */
  private String getLocationString(SAXParseException ex) 
  {
    StringBuffer str = new StringBuffer();

    String systemId = ex.getSystemId();
    if (systemId != null)
    {
      int index = systemId.lastIndexOf('/');
      if (index != -1)
        systemId = systemId.substring(index + 1);
      str.append(systemId);
    }
    str.append(':');
    str.append(ex.getLineNumber());
    str.append(':');
    str.append(ex.getColumnNumber());

    return str.toString();
  } // getLocationString(SAXParseException):String

  /** Main program entry point. */
  public static void main(String argv[]) 
  {
    if (argv.length == 0 ||
        (argv.length == 1 && argv[0].equals("-help")))
    {
      System.out.println("\nUsage:  java DomValidator uri dtd | schema");
      System.out.println("   where uri is the URI of the XML " + 
                         "document you want to ");
      System.out.println("   print, and dtd or schema is the " + 
                         "validation language.");
      System.out.println("\n   Sample:  java DomValidator sonnet.xml");
      System.out.println("\nParses an XML document, then writes " +
                         "any namespace information to the console.");
      System.exit(1);
    }

    boolean useSchema = true;
    if (argv.length == 2 && argv[1].equalsIgnoreCase("dtd"))
      useSchema = false;

    DomValidator dv = new DomValidator();
    dv.parseAndValidate(argv[0], useSchema);
  }
}
