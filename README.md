acdb_extract
========

This program fetches the true acdb ids and sound device names from the audio HAL using `dlopen()` and `dlsym()` to
run `platform_get_snd_device_*()` in the audio HAL.

This *will* have to be built using the android toolchain and pushed to an android device.

0. Generate the acdb_data header
   -> ./generate_acdb_data.sh $stock_audio_hal.so
0. Clone the repo and use the android toolchain to make the binary.
0. Run `./acdb_extract [path to audio hal] > acdb_table.txt` to save the table in `acdb_table.txt`.
0. Enjoy your acdb table

get_snd_dev_names
=================

This program fetches the true sound device names from the audio HAL using `dlopen()` and `dlsym()` to
run `platform_get_snd_device_name()` in the audio HAL.

This *will* have to be built using the android toolchain and pushed to an android device.

0. Generate the acdb_data header
   -> ./generate_acdb_data.sh $stock_audio_hal.so
0. Clone the repo and use the android toolchain to make the binary.
0. Run `./get_snd_dev_names [path to audio hal] > device_names.h` to save the table in `device_names.h`.
