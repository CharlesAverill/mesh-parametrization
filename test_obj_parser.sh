sh compile.sh > /dev/null

bold=$(tput bold)
red=$(tput setaf 1)
green=$(tput setaf 2)
reset=$(tput sgr0)

for obj_file in $(find objs -type f -name "*.obj"); do
    mp_output=$(bin/mesh-parametrization "$obj_file" 2>&1)
    mp_rc=$?

    # Check the return code
    if [ $mp_rc -ne 0 ]; then
        echo "${bold}${red}Error processing: $obj_file${reset}"
        echo "mp command returned non-zero exit code: $mp_rc"
        echo "Captured output:"
        echo "$mp_output"
        exit 1
    else
        echo "Processed: $obj_file"
    fi
done

echo "${bold}${green}All good!${reset}"
