BEGIN { RS="\n"; max=0; print "Extract number (Nº Records)"; }


$1 == 1  { if(extracts>max) max=extracts; extracts++; }
$1 != "" { lines[extracts]++; }


END { for(i in lines) {print "[*] #" i " (" lines[i] " lines)"};
      print "\nNumber of extracts: " extracts;
      print "Extract with most lines: " max " (" lines[max] " lines)";
    }
