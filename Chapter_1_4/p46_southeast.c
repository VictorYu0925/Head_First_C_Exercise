#include <stdio.h>

void go_south_east(int* address_of_lat, int* address_of_lon)
{
  *address_of_lat = *address_of_lat - 1;
  *address_of_lon = *address_of_lon + 1;
  /* check address
  printf("address of lat: %p , lon: %p\n", address_of_lat, address_of_lon);
  */
}

int main()
{
  int latitude = 32;
  int longitude = -64;
  go_south_east(&latitude,&longitude);
  printf("Avast! Now at [%i , %i]\n" ,latitude ,longitude);
  /* check address
  printf("Check address of lat: %p , lon: %p\n", &latitude, &longitude);
  */
  return 0;
}
