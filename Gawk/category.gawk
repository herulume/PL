BEGIN { RS="\n";  }

# $4 type
index($4, "V") == 1  {verbs[$3]++;}
index($4, "N") == 1  {nouns[$3]++;}
index($4, "A") == 1  {adjes[$3]++;}
index($4, "R") == 1  {adves[$3]++;}

END { for(i in adves){print i};}
