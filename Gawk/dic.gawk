function toHTML() {
   print "<!DOCTYPE html>\n<HTML><body>\n<meta charset=\"UTF-8\">\n<header>\n<h1>Implicit Dictionary</h1>\n</header>" > ARGV[1]"dic.html"
   print "<table border='1'>" > ARGV[1]"dic.html"
   print "<tr><td><b> Word </b></td><td><b> Lema </b></td><td><b> POS </b></td></tr>" >> ARGV[1]"dic.html"

   for (l in lemmas) {
    for(w in lemmas[l]){
        print "<tr><td>" w "</td><td>" l "</td><td>" lemmas[l][w] "</td></tr>" |" sort -k2n >> " ARGV[1]"dic.html";
   }
    }
}

BEGIN { RS="\n"; }

# $4 pos-tag
# $3 lemma
# $2 palavra
$3 ~ /^[a-zA-ZàÀáÁâÂãÃéÉèÈêÊẽẼíÍìÌîÎĩĨóÓòÒôÔõÕúÚùÙûÛũŨ][a-zàáâãéèêẽíìîĩóòôõúùûũ_\-]/  { lemmas[$3][$2]=$4; }

END { toHTML(); }
