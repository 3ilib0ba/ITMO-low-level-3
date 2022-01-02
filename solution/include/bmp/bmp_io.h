#include "image/image.h"

/*  deserializer   */
enum read_status  {
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  READ_PIXELS_ERROR,
  READ_ERROR
  /* коды других ошибок  */
};

enum read_status from_bmp( FILE* in, struct image *img );

/*  serializer   */
enum  write_status  {
  WRITE_OK = 0,
  WRITE_ERROR
  /* коды других ошибок  */
};

enum write_status to_bmp( FILE* out, struct image *img );
