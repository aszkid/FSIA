echo $(tput bold)$(tput setaf 5)"--------------------------------------------"
echo "--------------------------------------------"
echo $(tput bold)$(tput setaf 1)"----------------------"
echo "-- GENERATING CMAKE --"
echo "----------------------"$(tput sgr0)
if [ "$1" == "32" ]
then
	cmake -G"Unix Makefiles" pro/make_32/
	cd pro/make_32
elif [ "$1" == "64" ]
then
	cmake -G"Unix Makefiles" pro/make_64/
	cd pro/make_64
fi

make all
cd ../../bin
echo $(tput bold)$(tput setaf 1)"----------------------"
echo "-- RUNNING PROJECT  --"
echo "----------------------"$(tput sgr0)
./"$2"
cd ../
echo $(tput bold)$(tput setaf 1)"----------------------"
echo $(tput bold)$(tput setaf 5)"--------------------------------------------"
echo "--------------------------------------------"$(tput sgr0)
