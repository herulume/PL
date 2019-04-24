BEGIN { RS="\n";  }

# $4 pos-tag
# $3 lemma
# $2 palavra
$3 ~ /^[a-zA-ZàÀáÁâÂãÃéÉèÈêÊẽẼíÍìÌîÎĩĨóÓòÒôÔõÕúÚùÙûÛũŨ][a-zA-ZàÀáÁâÂãÃéÉèÈêÊẽẼíÍìÌîÎĩĨóÓòÒôÔõÕúÚùÙûÛũŨ\-_]*/  { lemmas[$3][$2]=$4; }

END {
    for(l in lemmas){
        { print "[*] Lemma: " l; }
        for(w in lemmas[l]){
            { print "\tWord: " w " <-> Pos: " lemmas[l][w]}
        };
    };

}
