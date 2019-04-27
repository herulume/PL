pat="[a-zA-Z]+\..+"
for file in *; do
    [ -f "$file" ] || continue
    if [[ ! $file =~ $pat ]]; then
        sh output.sh $file
    fi
done
