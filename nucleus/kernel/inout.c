
#include <kernel.h>

unsigned char inportb (unsigned short port)
{
  unsigned char _v;

  __asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (port));
  return _v;
}


void outportb (unsigned short port, unsigned char value)
{
  __asm__ __volatile__ ("outb %b0,%w1"::"a" (value), "Nd" (port));
}
