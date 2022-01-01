# Tugas-Besar-Embedded-


Nama : Randi Baraku
projek : Sistem monitoring tanaman menggunakan ESP 32 dan forward chaining algorithm
- feel free to use this repo and do not forget to add the credits :D

Penjelasan kode 
Kode yang dibangun merupakan kode yang mengimplementasikan algotima forwatd chaining.
Kode memiliki 8 rules yang harus dieksekusi oleh fakta untuk menghasilkan keputusan yang tepat oleh sistem
Fakta diperoleh dari 5 nilai yang diterima oleh sensor
sedangkan keputusan merupakan 2 aksi yang akan dilakukan oleh aktuator

Tata cara instalasi :
Siapakan board berupa ESP 32
siapkan library yang dibutuhkan yaitu : microservo, blynkIoT, LiquidCrytal (beserta I2C lybrary jika menggunkaan I2C pada LCD), dan DHT. disarankan menggunakan lybrary dafruit.
daftar terlebih dahulu pada akun Blynk, dan buatlah sebuah projek. 
Spesifikasi projek pada blynk haruslahmengikuti spesifikasi pada laporan. 
Buatlah dashboard seperti yang tertera pada laporan.
copy code autentifikasi yang ada pada projek yang anda buat.
ganti autentifikasi pada header code dengan autentifikasi projek anda.
Unduh blynk IoT dari smartphone anda, upload code dan lakukan pairing pada device. 
buatlah tampilan yang sama dengan dashboard desktop.
data sudah dapat dimonitoring melalui smartphone dan desktop.

Diagram arsitektur:
![This is an image](https://myoctocat.com/assets/images/base-octocat.svg)





Saran perbaikan :
gunakan rellay 3,3 v agar output dan input tegangan seimbang dengan pinout ESP32
jika mengalami masalah koneksi server, buatlah projek baru dan reupload projek lama untuk menimpa projek pada blynk.
