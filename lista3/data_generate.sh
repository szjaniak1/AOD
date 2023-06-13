#!/bin/bash

gr_suffix='.gr'
ss_suffix='.ss'
p2p_suffix='.p2p'
itr=1
readarray -t usa_graphs < <(ls ./generator/inputs/USA-road-d/*.gr)
readarray -t rand_graphs < <(ls ./generator/inputs/Random4-C/*.gr)
readarray -t square_graphs < <(ls ./generator/inputs/Square-C/*.gr)
readarray -t long_graphs < <(ls ./generator/inputs/Long-n/*.gr)

make dial
make radix
make

if [ $1 -eq 1 ] 
then
    rm -rf usa_data.txt
    rm -rf rand_data.txt
    rm -rf square_data.txt
    rm -rf long_data.txt

    for ugr in "${usa_graphs[@]}";
    do
        cpy=${ugr}
        ss=${ugr//$gr_suffix/$ss_suffix}
        echo "${ss}" >> usa_data.txt
        echo "./dijkstra -d ${cpy} -ss ${ss} -oss usa_data.txt"
        ./dijkstra -d "${cpy}" -ss "${ss}" -oss usa_data.txt
        echo "./dial -d ${cpy} -ss ${ss} -oss usa_data.txt"
        ./dial -d "${cpy}" -ss "${ss}" -oss usa_data.txt
        echo "./radix -d ${cpy} -ss ${ss} -oss usa_data.txt"
        ./radix -d "${cpy}" -ss "${ss}" -oss usa_data.txt
        echo "USA ${itr}/${#usa_graphs[@]}"
        itr=$((itr+1))
    done

    itr=1
    for rgr in "${rand_graphs[@]}";
    do
        cpy=${rgr}
        ss=${rgr//$gr_suffix/$ss_suffix}
        echo "${ss}" >> rand_data.txt
        echo "./dijkstra -d ${cpy} -ss ${ss} -oss rand_data.txt"
        ./dijkstra -d "${cpy}" -ss "${ss}" -oss rand_data.txt
        echo "./dial -d ${cpy} -ss ${ss} -oss rand_data.txt"
        ./dial -d "${cpy}" -ss "${ss}" -oss rand_data.txt
        echo "./radix -d ${cpy} -ss ${ss} -oss rand_data.txt"
        ./radix -d "${cpy}" -ss "${ss}" -oss rand_data.txt
        echo "RAND ${itr}/${#rand_graphs[@]}"
        itr=$((itr+1))
    done

    itr=1
    for sgr in "${square_graphs[@]}";
    do
        cpy=${sgr}
        ss=${sgr//$gr_suffix/$ss_suffix}
        echo "${ss}" >> square_data.txt
        echo "./dijkstra -d ${cpy} -ss ${ss} -oss square_data.txt"
        ./dijkstra -d "${cpy}" -ss "${ss}" -oss square_data.txt
        echo "./dial -d ${cpy} -ss ${ss} -oss square_data.txt"
        ./dial -d "${cpy}" -ss "${ss}" -oss square_data.txt
        echo "./radix -d ${cpy} -ss ${ss} -oss square_data.txt"
        ./radix -d "${cpy}" -ss "${ss}" -oss square_data.txt
        echo "SQUARE ${itr}/${#square_graphs[@]}"
        itr=$((itr+1))
    done

    itr=1
    for lgr in "${long_graphs[@]}";
    do
        cpy=${lgr}
        ss=${lgr//$gr_suffix/$ss_suffix}
        echo "${ss}" >> long_data.txt
        echo "./dijkstra -d ${cpy} -ss ${ss} -oss long_data.txt"
        ./dijkstra -d "${cpy}" -ss "${ss}" -oss long_data.txt
        echo "./dial -d ${cpy} -ss ${ss} -oss long_data.txt"
        ./dial -d "${cpy}" -ss "${ss}" -oss long_data.txt
        echo "./radix -d ${cpy} -ss ${ss} -oss long_data.txt"
        ./radix -d "${cpy}" -ss "${ss}" -oss long_data.txt
        echo "LONG ${itr}/${#long_graphs[@]}"
        itr=$((itr+1))
    done
else
    rm -rf usa_datap2p.txt
    rm -rf rand_datap2p.txt
    rm -rf square_datap2p.txt
    rm -rf long_datap2p.txt

    # for ugr in "${usa_graphs[@]}";
    # do
    #     cpy=${ugr}
    #     ss=${ugr//$gr_suffix/$p2p_suffix}
    #     echo "${p2p}" >> usa_data.txt
    #     echo "./dijkstra -d ${cpy} -ss ${ss} -oss usa_data.txt"
    #     ./dijkstra -d "${cpy}" -ss "${ss}" -oss usa_data.txt
    #     echo "./dial -d ${cpy} -ss ${ss} -oss usa_data.txt"
    #     ./dial -d "${cpy}" -ss "${ss}" -oss usa_data.txt
    #     echo "./radix -d ${cpy} -ss ${ss} -oss usa_data.txt"
    #     ./radix -d "${cpy}" -ss "${ss}" -oss usa_data.txt
    #     echo "USA ${itr}/${#usa_graphs[@]}"
    #     itr=$((itr+1))
    # done

    itr=1
    for rgr in "${rand_graphs[@]}";
    do
        cpy=${rgr}
        p2p=${rgr//$gr_suffix/$p2p_suffix}
        echo "${ss}" >> rand_datap2p.txt
        echo "./dijkstra -d ${cpy} -p2p ${p2p} -op2p rand_datap2p.txt"
        ./dijkstra -d "${cpy}" -p2p "${p2p}" -op2p rand_datap2p.txt
        echo "./dial -d ${cpy} -p2p ${p2p} -op2p rand_datap2p.txt"
        ./dial -d "${cpy}" -p2p "${p2p}" -op2p rand_datap2p.txt
        echo "./radix -d ${cpy} -p2p ${p2p} -op2p rand_datap2p.txt"
        ./radix -d "${cpy}" -p2p "${p2p}" -op2p rand_datap2p.txt
        echo "RAND ${itr}/${#rand_graphs[@]}"
        itr=$((itr+1))
    done

    # itr=1
    # for sgr in "${square_graphs[@]}";
    # do
    #     cpy=${sgr}
    #     ss=${sgr//$gr_suffix/$ss_suffix}
    #     echo "${ss}" >> square_data.txt
    #     echo "./dijkstra -d ${cpy} -ss ${ss} -oss square_data.txt"
    #     ./dijkstra -d "${cpy}" -ss "${ss}" -oss square_data.txt
    #     echo "./dial -d ${cpy} -ss ${ss} -oss square_data.txt"
    #     ./dial -d "${cpy}" -ss "${ss}" -oss square_data.txt
    #     echo "./radix -d ${cpy} -ss ${ss} -oss square_data.txt"
    #     ./radix -d "${cpy}" -ss "${ss}" -oss square_data.txt
    #     echo "SQUARE ${itr}/${#square_graphs[@]}"
    #     itr=$((itr+1))
    # done

    # itr=1
    # for lgr in "${long_graphs[@]}";
    # do
    #     cpy=${lgr}
    #     ss=${lgr//$gr_suffix/$ss_suffix}
    #     echo "${ss}" >> long_data.txt
    #     echo "./dijkstra -d ${cpy} -ss ${ss} -oss long_data.txt"
    #     ./dijkstra -d "${cpy}" -ss "${ss}" -oss long_data.txt
    #     echo "./dial -d ${cpy} -ss ${ss} -oss long_data.txt"
    #     ./dial -d "${cpy}" -ss "${ss}" -oss long_data.txt
    #     echo "./radix -d ${cpy} -ss ${ss} -oss long_data.txt"
    #     ./radix -d "${cpy}" -ss "${ss}" -oss long_data.txt
    #     echo "LONG ${itr}/${#long_graphs[@]}"
    #     itr=$((itr+1))
    # done
fi


make clean
