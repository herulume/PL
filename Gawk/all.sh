pat="[a-zA-Z]+\..+"


echo "<!DOCTYPE html>" > "index.html";
echo "<HTML>" >> "index.html";
echo "<body>" >> "index.html";
echo "<header><h1> Welcome to the best PL zine around!</h1></header>" >> "index.html";
echo "<h2>Files to checkout:</h2>" >> "index.html";

for file in *; do
    [ -f "$file" ] || continue
    if [[ ! $file =~ $pat ]]; then
        sh output.sh $file
        echo "<h3><a href=\"$file""_index.html\">$file</a></h3>" >> "index.html";
    fi
done


echo "</body>" >> "index.html";
