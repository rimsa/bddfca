#ifndef _OBJECT_H
#define _OBJECT_H

class Object {
  private:
    int lngth;
    int flld;
    char *bits;
  public:
    Object(int length);
    ~Object( );

    int length( );
    int filled( );

    void set(int idx, bool value);
    void set(int idx);
    bool get(int idx);

    const char *toString( );
};

#endif
