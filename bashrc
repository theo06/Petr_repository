# Make
make_func() {
    if [ $# -eq 2 ]; then
        case $2 in
            dev)
                args="$1 COMMAND=dev"
                ;;
            lib)
                args="$1 COMMAND=lib"
                ;;
            test)
                args="$1 COMMAND=mu_tests"
                ;;
            *)
                args=$@
                ;;
        esac
    else
        args=$@
    fi

    cerr=$(echo -e "\033[1;31m")
    cwarn=$(echo -e "\033[1;35m")
    cdbg=$(echo -e "\033[1;33m")
    cbold=$(echo -e "\033[1;39m")
    cend=$(echo -e "\033[0m")

    grc make $args | sed -E -e "s%(error)\ (\(.*?\):)%$cerr\1 $cbold\2$cend%g" \
        -e "s%(warning)\ (\(.*?\):)%$cwarn\1 $cbold\2$cend%g" \
        -e "s%(info)\ (\(.*?\):)%$cbold\1 \2$cend%g" \
        -e "s%(debug)\ (\(.*?\):)%$cdbg\1 $cbold\2$cend%g" \
        -e "s%FAILED%$cerr&$cend%g"
}

alias make=make_func
