#include <iostream>

using namespace std;
#include <cmath>

#include <QTextStream>
#include <QFile>

const QString dat_str =
    "ObjectFileName: %1                     \n"
    "Resolution:     %2 %3 %4                   \n"
    "Format:         USHORT                     \n"
    "SliceThickness: 1.0 1.0 1.0                \n"
    "ObjectType:     TEXTURE_VOLUME_OBJECT      \n"
    "ObjectModel:    I                          \n"
    "GridType:       EQUIDISTANT                \n";

void gen_cube(){
  std::cout << "START" << std::endl;
  const int kCubeSide = 250;
  const int kCubeSize = kCubeSide*kCubeSide*kCubeSide;

  unsigned short *data = new unsigned short[kCubeSize];

  QFile raw_file("cube.raw");
  QFile dat_file("cube.dat");

  if( !raw_file.open(QIODevice::WriteOnly) ) return;
  if( !dat_file.open(QIODevice::WriteOnly | QIODevice::Text) ) return;

  QTextStream out(&dat_file);
  out << dat_str.arg(raw_file.fileName(),QString::number(kCubeSide),QString::number(kCubeSide),QString::number(kCubeSide));
  dat_file.close();

    std::cout << "WILL ENTER LOOP" << std::endl;
  for(int i=0;i<kCubeSide;i++){
    std::cout << "i" << i << "of" << kCubeSide << std::endl;
    for(int j=0;j<kCubeSide;j++){
      for(int k=0;k<kCubeSide;k++){
        data[i + kCubeSide*j + kCubeSide*kCubeSide*k] = max(abs((kCubeSide/2)-i),max(abs((kCubeSide/2)-j),abs((kCubeSide/2)-k)));
//        std::cout << i + kCubeSide*j + kCubeSide*kCubeSide*k << " of " << kCubeSize << std::endl;
//        std::cout << abs((kCubeSide/2)-i) 1+ abs((kCubeSide/2)-j) + abs((kCubeSide/2)-k) << std::endl;
      }
    }
  }
  QByteArray data_array((char*)data,sizeof(unsigned short)*kCubeSize);
  raw_file.write(data_array);
  std::cout << "END" << std::endl;
  delete[] data;
}

void gen_sphere(){
  std::cout << "START" << std::endl;
  const int kCubeSide = 250;
  const int kCubeSize = kCubeSide*kCubeSide*kCubeSide;

  unsigned short *data = new unsigned short[kCubeSize];

  QFile raw_file("sphere.raw");
  QFile dat_file("sphere.dat");

  if( !raw_file.open(QIODevice::WriteOnly) ) return;
  if( !dat_file.open(QIODevice::WriteOnly | QIODevice::Text) ) return;

  QTextStream out(&dat_file);
  out << dat_str.arg(raw_file.fileName(),QString::number(kCubeSide),QString::number(kCubeSide),QString::number(kCubeSide));
  dat_file.close();

    std::cout << "WILL ENTER LOOP" << std::endl;
  for(int i=0;i<kCubeSide;i++){
    std::cout << "i" << i << "of" << kCubeSide << std::endl;
    for(int j=0;j<kCubeSide;j++){
      for(int k=0;k<kCubeSide;k++){
        data[i + kCubeSide*j + kCubeSide*kCubeSide*k] = kCubeSide - sqrt((pow((kCubeSide/2)-i,2) + pow((kCubeSide/2)-j,2) + pow((kCubeSide/2)-k,2))) - 30;
//        std::cout << i + kCubeSide*j + kCubeSide*kCubeSide*k << " of " << kCubeSize << std::endl;
//        std::cout << abs((kCubeSide/2)-i) 1+ abs((kCubeSide/2)-j) + abs((kCubeSide/2)-k) << std::endl;
      }
    }
  }
  QByteArray data_array((char*)data,sizeof(unsigned short)*kCubeSize);
  raw_file.write(data_array);
  std::cout << "END" << std::endl;
  delete[] data;
}

int main()
{
//  gen_cube();
  gen_sphere();

  return 0;
}

