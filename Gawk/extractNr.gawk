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
      print Red "[*]" Gray " Number of extracts: " Green exctratNr NoColour;
      print Red "[*]" Gray " Extract with the most lines: " Green max Gray " with " Green lines[max] Gray " lines" NoColour;
      print Red "[*]" Gray " Extract with the least lines: " Green min Gray " with " Green lines[min] Gray " lines" NoColour;
      print Red "[*]" Gray " Average lines per extract: " Green sum/exctratNr NoColour;
    }