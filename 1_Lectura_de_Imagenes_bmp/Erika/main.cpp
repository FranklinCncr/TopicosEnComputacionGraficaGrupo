#include <iostream>
#include <vector>
#include <fstream>

#pragma once
#include <stdexcept>
#pragma pack(push, 1)
using namespace std;
struct BMP_file_cabecera {
    uint16_t file_type{ 0x4D42 };          // File type always BM which is 0x4D42 (stored as hex uint16_t in little endian)
    uint32_t file_size{ 0 };               // Size of the file (in bytes)
    uint16_t reserved1{ 0 };               // Reserved, always 0
    uint16_t reserved2{ 0 };               // Reserved, always 0
    uint32_t offset_data{ 0 };             // Start position of pixel data (bytes from the beginning of the file)
};

struct BMP_info_cabecera {
    uint32_t size{ 0 };
    int32_t width{ 0 };//ancho de pixeles
    int32_t height{ 0 };//ancho de bitmap positivo a la izquiera esta
                        //ancho de abajo hacia arriba con
    uint16_t planes{ 1 };                    // No. of planes for the target device, this is always 1
    uint16_t bit_count{ 0 }; //Numero de pixeles
    uint32_t compression{ 0 };               // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
    uint32_t size_image{ 0 };                // 0 - for uncompressed images
    int32_t x_pixels_per_meter{ 0 };
    int32_t y_pixels_per_meter{ 0 };
    uint32_t colors_used{ 0 };               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
    uint32_t colors_important{ 0 };          // No. of colors used for displaying the bitmap. If 0 all colors are required
};
struct BMP_color {
    uint32_t red_mask{ 0x00ff0000 };         // mascara del canal rojo
    uint32_t green_mask{ 0x0000ff00 };       // mascara del canal verde
    uint32_t blue_mask{ 0x000000ff };        // mascara del canal azul
    uint32_t alpha_mask{ 0xff000000 };       // mascara del canal de alfa
    uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
    uint32_t unused[16]{ 0 };                // Unused data for sRGB color space
};

struct BMP {
    BMP_file_cabecera file_header;
    BMP_info_cabecera bmp_info_header;
    BMP_color bmp_color_header;
    vector<uint8_t> datos;

    BMP(const char *fname) {
        leer(fname);
    }
    void leer(const char *fname) {
        ifstream inp{ fname, ios_base::binary};
        if (inp) {

            inp.read((char*)&file_header, sizeof(file_header));

            if(file_header.file_type != 0x4D42) {
                throw runtime_error("Error! Unrecognized file format.");
            }
            inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));
            //Establece la posición del siguiente carácter que se extraerá de la secuencia de entrada.
            //inp.beg comienzo del string
            inp.seekg(file_header.offset_data, inp.beg);

            // Adjust the header fields for output.
            // Some editors will put extra info in the image file, we only save the headers and the data.
            /*if(bmp_info_header.bit_count == 32) {
                bmp_info_header.size = sizeof(bmp_info_header) + sizeof(bmp_color);
                file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
            } else {
                bmp_info_header.size = sizeof(BMPInfoHeader);
                file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
            }*/

            file_header.file_size = file_header.offset_data;
            cout<<"Tipo de archivo"<<(char)file_header.file_type<<endl;
            cout<<"Tamano de la imagen"<<(int)file_header.file_size<<endl;
            cout<<"Alto de la imagen"<<(int)bmp_info_header.height<<endl;
            cout<<"Los colores usados"<<bmp_info_header.colors_used<<endl;
            cout<<"Pixel que comienza los datos"<<file_header.offset_data<<endl;
            cout<<"Número de pixeles "<<bmp_info_header.bit_count<<endl;
            cout<<"Ancho  "<<bmp_info_header.width<<endl;
            cout<<"Alto "<<bmp_info_header.height<<endl;

            if (bmp_info_header.height < 0) {
                throw runtime_error("El programa solo se puede tratar con imagenes que comienza en la esquina");
            }

            datos.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);

            // Here we check if we need to take into account row padding
            if (bmp_info_header.width % 4 == 0) {
                inp.read((char*)datos.data(), datos.size());
                file_header.file_size += static_cast<uint32_t>(datos.size());
            }
            else {
                int row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
                uint32_t new_stride = make_stride_aligned(4);
                vector<uint8_t> padding_row(new_stride - row_stride);

                for (int y = 0; y < bmp_info_header.height; ++y) {
                    inp.read((char*)(datos.data() + row_stride * y), row_stride);
                    inp.read((char*)padding_row.data(), padding_row.size());
                }
                file_header.file_size += static_cast<uint32_t>(datos.size()) + bmp_info_header.height * static_cast<uint32_t>(padding_row.size());
            }
        }
        else {
            throw runtime_error("No se puede abrir la imágen");
        }
    }

    void escribir(const char *fname) {
        ofstream of{ fname, ios_base::binary };
        if (of) {
            if (bmp_info_header.bit_count == 32) {
                escribe_cabeceras(of);
            }
            else if (bmp_info_header.bit_count == 24) {
                if (bmp_info_header.width % 4 == 0) {
                    escribe_cabeceras(of);
                }
                else {
                    uint32_t new_stride = make_stride_aligned(4);
                    vector<uint8_t> padding_row(new_stride - row_stride);

                    escribe_cabeceras(of);

                    for (int y = 0; y < bmp_info_header.height; ++y) {
                        //pasos row_ stride
                        of.write((const char*)(datos.data() + row_stride * y), row_stride);
                        of.write((const char*)padding_row.data(), padding_row.size());
                    }
                }
            }
            else {
                throw runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
            }
        }
        else {
            throw std::runtime_error("Unable to open the output image file.");
        }
    }
    ///Escribe una region en los datos de entrada
    void crear_forma(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint8_t R, uint8_t G, uint8_t B, uint8_t A) {

        if (x0 + w > (uint32_t)bmp_info_header.width || y0 + h > (uint32_t)bmp_info_header.height) {
            throw runtime_error("La region no se puede pintar!");
        }

        uint32_t channels = bmp_info_header.bit_count / 8;
        //cada canal es de 8 bits
        cout<<"datos"<<channels<<endl;
        for (uint32_t y = y0; y < y0 + h; ++y) {
            for (uint32_t x = x0; x < x0 + w; ++x) {
                datos[channels * (y * bmp_info_header.width + x) + 0] = B;
                datos[channels * (y * bmp_info_header.width + x) + 1] = G;
                datos[channels * (y * bmp_info_header.width + x) + 2] = R;
            }
        }
    }

private:
    uint32_t row_stride{ 0 };

     void escribe_cabe_info_file( ofstream &of) {
        of.write((const char*)&file_header, sizeof(file_header));
        of.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
        if(bmp_info_header.bit_count == 32) {
            of.write((const char*)&bmp_color_header, sizeof(bmp_color_header));
        }
    }

     void escribe_cabeceras(ofstream &of) {
        escribe_cabe_info_file(of);
        of.write((const char*)datos.data(), datos.size());
    }

    // Add 1 to the row_stride until it is divisible with align_stride
    uint32_t make_stride_aligned(uint32_t align_stride) {
        uint32_t new_stride = row_stride;
        while (new_stride % align_stride != 0) {
            new_stride++;
        }
        return new_stride;
    }
};
int main()
{
    BMP bmp9("poesia.bmp");
    int pasos_li_h=10;
    int pasos_li_v=10;
    while( pasos_li_h+pasos_li_h+2<bmp9.bmp_info_header.width & pasos_li_v+pasos_li_v+2<bmp9.bmp_info_header.height){
    bmp9.crear_forma(pasos_li_h, pasos_li_v,pasos_li_h+2, pasos_li_v+2,8,140,126,0); //c , ,0, 1, 0, 0);
    pasos_li_h+=2;
    pasos_li_v+=2;
    }
    bmp9.crear_forma(0, 0,bmp9.bmp_info_header.width, 10,175,31,247,0);
    bmp9.escribir("poesia_linea.bmp");
    cout << "Hello world!" << endl;
    return 0;
}
