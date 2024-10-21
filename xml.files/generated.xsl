<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

 <xsl:output method="html"/>

 <xsl:template match="item/*">
    <xsl:element name="td">
	<xsl:value-of select="."/>
    </xsl:element>
 </xsl:template>
 
 <xsl:template match="item">
    <xsl:element name="tr">
	<xsl:apply-templates/>
    </xsl:element>
 </xsl:template>
 
 <xsl:template match="shipto">
    <xsl:for-each select="*">
	<xsl:element name="tr">
	    <xsl:element name="td">
		<xsl:text>Shipment </xsl:text>
		<xsl:copy-of select="name()"/>
	    </xsl:element>
	    <xsl:element name="td">
		<xsl:value-of select="."/>
	    </xsl:element>
	
	</xsl:element>
    </xsl:for-each>
 </xsl:template>
 
 <xsl:template match="shiporder">
    <xsl:element name="BR"/>

    <xsl:element name="table">
	<xsl:attribute name="width">600</xsl:attribute>
	<xsl:element name="tr">
	    <xsl:attribute name="style">background-color: #87CEFA</xsl:attribute>
	    <xsl:element name="th">
		<xsl:attribute name="colspan">2</xsl:attribute>
		<xsl:value-of select="@orderid"/>
	    </xsl:element>
	</xsl:element>
	<xsl:element name="tr">
	    <xsl:element name="td">
		<xsl:attribute name="width">200</xsl:attribute>
		<xsl:text>Person</xsl:text>
	    </xsl:element>
	    <xsl:element name="td">
		<xsl:value-of select="orderperson"/>
	    </xsl:element>
	</xsl:element>
	<xsl:apply-templates select="shipto"/>
	<xsl:element name="tr">
	    <xsl:element name="td">    
		<xsl:attribute name="colspan">2</xsl:attribute>
		<xsl:element name="table">
		    <xsl:attribute name="border">1</xsl:attribute>
		    <xsl:attribute name="width">500</xsl:attribute>
		    <xsl:attribute name="align">center</xsl:attribute>
		    <xsl:element name="tr">
		    	<xsl:attribute name="style">background-color: #ACACAC</xsl:attribute>
		    	<xsl:element name="th">Title</xsl:element>
			<xsl:element name="th">Note</xsl:element>
			<xsl:element name="th">Quantity</xsl:element>
			<xsl:element name="th">Price</xsl:element>
		    </xsl:element>
		    <xsl:apply-templates select="item"/>
		</xsl:element>
	    </xsl:element>
	</xsl:element>
    </xsl:element>
 </xsl:template>

 <xsl:template match="/">
    <html>
      <head>
	<title>Order List</title>
      </head>
      <body>
	<xsl:apply-templates/>
      </body>
    </html>
 </xsl:template>
</xsl:stylesheet>
