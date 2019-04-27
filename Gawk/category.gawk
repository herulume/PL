function toHTML(type, header, info) {
   print "<!DOCTYPE html>\n<HTML><body>\n<meta charset=\"UTF-8\">\n<header>\n<h1>" header "</h1>\n</header>" > type".html"
   print "<table border='1'>" > type".html"
   print "<tr><td><b> Word </b></td><td><b> Number of occurrences </b></td></tr>" >> type".html"

   for (w in info) {
        print "<tr><td>" w "</td><td>" info[w] "</td></tr>" |" sort -k2n >> " type".html";
   }
}

BEGIN { RS="\n";  }

# $4 type
index($4, "V") == 1  {verbs[$2]++;}
index($4, "N") == 1  {nouns[$2]++;}
index($4, "A") == 1  {adjes[$2]++;}
index($4, "R") == 1  {adves[$2]++;}

END {
    toHTML("verbs", "List of verbs!", verbs);
    toHTML("nouns", "List of nouns!", nouns);
    toHTML("adjes", "List of adjectives!", adjes);
    toHTML("adves", "List of adverbs!", adves);
}
