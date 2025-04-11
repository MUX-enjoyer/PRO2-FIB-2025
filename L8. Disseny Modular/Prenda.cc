#include "Prenda.hh"

Prenda::Prenda()
{
  peso = 0;
  color = false;
}

Prenda::Prenda(int pes, bool col)
{
  peso = pes;
  color = col;
}

void Prenda::modificar(int pes, bool col)
{
  peso = pes;
  color = col;
}

int Prenda::consul_peso() const
{
  return peso;
}

bool Prenda::consul_color() const
{
  return color;
}

void Prenda::escribir() const
{
  cout << peso << ' ';
  if (color) cout << "true" << endl;
  else cout << "false" << endl;
}