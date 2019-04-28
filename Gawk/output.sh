gawk -f dic.gawk $1
gawk -f category.gawk $1
gawk -f extractNr.gawk $1


echo "<!DOCTYPE html>" > "$1_index.html";
echo "<HTML>" >> "$1_index.html";
echo "<body>" >> "$1_index.html";
echo "<header><h1> All about $1!</h1></header>" >> "$1_index.html";
echo "<h3><a href=\"$1eNr.html\">Info about the extracts</a></h3>" >> "$1_index.html";
echo "<h3><a href=\"$1dic.html\">Implicit Dictionary</a></h3>" >> "$1_index.html";
echo "<h3><a href=\"$1nouns.html\">Nouns</a></h3>" >> "$1_index.html";
echo "<h3><a href=\"$1verbs.html\">Verbs</a></h3>" >> "$1_index.html";
echo "<h3><a href=\"$1adves.html\">Adverbs</a></h3>" >> "$1_index.html";
echo "<h3><a href=\"$1adjes.html\">Adjectives</a></h3>" >> "$1_index.html";
echo "</body>" >> "$1_index.html";
