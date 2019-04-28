gawk -f harrypotterNP.gawk $1


echo "<!DOCTYPE html>" > "$1_index.html";
echo "<HTML>" >> "$1_index.html";
echo "<body>" >> "$1_index.html";
echo "<header><h1> All about $1!</h1></header>" >> "$1_index.html";
echo "<h3><a href=\"$1hp.html\">Info about the proper nouns</a></h3>" >> "$1_index.html";
echo "</body>" >> "$1_index.html";
