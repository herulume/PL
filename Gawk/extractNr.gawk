function toHTML(){
    print "<!DOCTYPE html>\n<HTML>\n<body>\n<header><h1>" ARGV[1] " extract metrics!</h1></header>\n" > ARGV[1]"eNr.html";
    print "\t<h3>Number of extracts: " exctratNr "</h3>\n" >> ARGV[1]"eNr.html";
    print "<h3>Extract with the most lines: " max "</h3>\n" >> ARGV[1]"eNr.html";
    print "<h3>Extract with the least lines: " min "</h3>\n" >> ARGV[1]"eNr.html";
    print "<h3>Average lines per extract: " sum/ exctratNr "</h3>\n" >> ARGV[1]"eNr.html";
    print "</body>" >> ARGV[1]"eNr.html";
}

BEGIN { RS="\n";
        max=0; min=2^1024; exctratNr=0;
        Red="\033[0;31m"
        Yellow="\033[1;33m"
        Gray="\033[1;30m"
        Green="\033[32m"
        NoColour="\033[0m"
      }


$1 == 1 {   if(exctratNr != 0) {
                if(lines[exctratNr]>max)
                    max=exctratNr;
                if(lines[exctratNr]<min)
                    min=exctratNr;
            }
            exctratNr++;
        }

$1 != "" { lines[exctratNr]++; }


END { sum=0; for(nr in lines) sum += nr;
      toHTML();
      print Red "[*]" Gray " Number of extracts: " Green exctratNr NoColour;
      print Red "[*]" Gray " Extract with the most lines: " Green max Gray " with " Green lines[max] Gray " lines" NoColour;
      print Red "[*]" Gray " Extract with the least lines: " Green min Gray " with " Green lines[min] Gray " lines" NoColour;
      print Red "[*]" Gray " Average lines per extract: " Green sum/exctratNr NoColour;
    }
