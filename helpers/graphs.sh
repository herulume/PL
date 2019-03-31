cd output/tags
for file in *.dot; do
    [ -f "$file" ] || continue 
    dot -Tpng "$file" -o "$file.png"
done
