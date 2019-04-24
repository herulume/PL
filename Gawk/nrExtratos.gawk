BEGIN { RS="\n"; print "NºExtract -> NºRecords"; }

$1 == 1 {extracts++;}
$1 != "" {lines[extracts]++;}


END { for(i in lines) {print i " -> " lines[i] }; print "\nTotal Extracts: " extracts;}
