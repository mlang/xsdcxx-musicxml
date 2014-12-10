#ifndef DOM_PARSE
#define DOM_PARSE

#include <string>
#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <memory>

// Parse an XML document from the standard input stream with an
// optional resource id. Resource id is used in diagnostics as
// well as to locate schemas referenced from inside the document.
//
std::unique_ptr<xercesc::DOMDocument>
parse (std::istream& is, const std::string& id, bool validate);

#endif // DOM_PARSE
