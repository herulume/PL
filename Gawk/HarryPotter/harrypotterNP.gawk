BEGIN { RS="\n";  }

# $2 is the word
$5 == "NP"  {words[$2]++;}

END { for(i in words){print i " -> " words[i]};}
