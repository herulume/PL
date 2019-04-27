BEGIN { RS="\n";  }

# $4 type
index($4, "V") == 1  {verbs[$2]++;}
index($4, "N") == 1  {nouns[$2]++;}
index($4, "A") == 1  {adjes[$2]++;}
index($4, "R") == 1  {adves[$2]++;}

END { for(i in adves){print i};}
