function toHTML() {
   print "<!DOCTYPE html>\n<HTML><body>\n<meta charset=\"UTF-8\">\n<header>\n<h1> List of all proper names present in Harry Potter!</h1>\n</header>" > ARGV[1]"hp.html";
   print "<table border='1'>" >> ARGV[1]"hp.html";
   print "<tr><td><b> Name </b></td><td><b> Number of occurrences </b></td></tr>" >> ARGV[1]"hp.html";

   for (name in names) {
        print "<tr><td>" name "</td><td>" names[name] "</td></tr>" |" sort -k2n >> " ARGV[1]"hp.html";
   };
}

BEGIN { RS="\n";  }

# $2 name
# $5 pos
$5 == "NP"  {names[$2]++;}

END { toHTML(); }
