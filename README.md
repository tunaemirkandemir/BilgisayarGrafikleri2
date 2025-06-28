# Kayıp Top – OpenGL Kısa Animasyon Projesi 🎮🌲

Bu proje, bir çocuğun gece vakti ormanda kaybolan topunu aradığı kısa animasyon hikayesini modern OpenGL kullanarak görselleştirir. Kullanıcı, karar verme anlarında hikayeye yön verirken sahne, aydınlatma ve kamera geçişleriyle sinematik bir deneyim sunar.

---

## 🎬 Hikaye

Bir çocuk gece ormanda oynarken topunu kaybeder. El fenerini bulup yaktığında karanlık ormanın içine doğru ilerlemeye başlar. Önünde iki yol çıkar: bir patika ve ormanın karanlık kısmı. Seçime göre hikaye ilerler: yanlış yola giderse topu bulamaz, doğru yolu seçerse korkutucu bir sesle karşılaşır ama sonunda topuna kavuşur.

---

## 🛠️ Özellikler

- 🌲 **Gerçekçi Orman Ortamı**: Ağaçlar, çalılar, orman zemin dokusu.
- 🔦 **El Feneri Işığı**: Spotlight efekti, sadece aktifken çevreyi aydınlatır.
- 🎧 **Ses Efektleri**: Orman ambiyansı, fener açma sesi, korku ve sevinç sesleri.
- 🎥 **Çoklu Kamera Modları**:
  - Birinci şahıs (FPS)
  - Üçüncü şahıs (TP)
  - Yukarıdan bakış (Overhead)
  - Serbest kamera (Free cam – WASD + fare)
- 🧠 **Hikaye Seçimi**: Kullanıcı tuşlarla yön verir (1 → Patika, 2 → Orman).
- 🧍 **Karakter Animasyonu**: Yürüme animasyonu ve otomatik hareketler.

---

## 🧰 Kullanılan Teknolojiler ve Kütüphaneler

- **OpenGL 3.3 Core** – Grafik render
- **GLFW** – Pencere, giriş kontrolü
- **GLAD** – OpenGL fonksiyon yükleyici
- **GLM** – Matris ve vektör hesaplamaları
- **stb_image / stb_easy_font** – Texture ve metin çizimi
- **WinMM** – Windows ses fonksiyonu ile ses çalma (PlaySound)

---

## 🗺️ Sahne ve Mimari

### 🎞️ Yapılar:
- `Scene` sınıfı: Ağaçlar, zemin, patika ve top objelerini çizer.
- `Character` sınıfı: Ana karakterin pozisyonu, yönü, animasyonu.

### 🔦 Shader Yapısı:
- **Vertex Shader**: Model, view, projection matrisleri ile nesneleri dönüştürür.
- **Fragment Shader**: Ambient + spotlight + specular bileşenlerle gerçekçi aydınlatma sağlar.
- Fener açık değilken ambient düşüktür, fener açıldığında ışık efektleri etkinleşir.

---

## 🔁 Kullanıcı Etkileşimi

| Tuşlar       | İşlev                                       |
|--------------|----------------------------------------------|
| `E`          | Feneri yak                                   |
| `1 / 2`      | Yol seç (Patika / Orman)                     |
| `WASD + Fare`| Serbest kamera modunda gezinti               |
| `C`          | Kamera modları arasında geçiş yap            |
| `ESC`        | Uygulamadan çıkış                            |

---

## 🧪 Derleme & Çalıştırma

```bash
mkdir build
cd build
cmake ..
make
./KayıpTop
