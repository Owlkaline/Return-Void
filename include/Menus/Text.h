#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "../defines.h"

#include "../Namespaces/LoadTexture.h"

class Text {
  public:
    
    void draw();
    void setup(float x, float y, char* text);
  protected:
    int x, y, width, height;
    std::string text;
    GLuint textures[50];
    
    static GLuint getLetter(char letter) {
      static GLuint A = txt::LoadTexture("Textures/Menu/Letters/A.png");
      static GLuint B = txt::LoadTexture("Textures/Menu/Letters/B.png");
      static GLuint C = txt::LoadTexture("Textures/Menu/Letters/C.png");
      static GLuint D = txt::LoadTexture("Textures/Menu/Letters/D.png");
      static GLuint E = txt::LoadTexture("Textures/Menu/Letters/E.png");
      static GLuint F = txt::LoadTexture("Textures/Menu/Letters/F.png");
      static GLuint G = txt::LoadTexture("Textures/Menu/Letters/G.png");
      static GLuint H = txt::LoadTexture("Textures/Menu/Letters/H.png");
      static GLuint I = txt::LoadTexture("Textures/Menu/Letters/I.png");
      static GLuint J = txt::LoadTexture("Textures/Menu/Letters/J.png");
      static GLuint K = txt::LoadTexture("Textures/Menu/Letters/K.png");
      static GLuint L = txt::LoadTexture("Textures/Menu/Letters/L.png");
      static GLuint M = txt::LoadTexture("Textures/Menu/Letters/M.png");
      static GLuint N = txt::LoadTexture("Textures/Menu/Letters/N.png");
      static GLuint O = txt::LoadTexture("Textures/Menu/Letters/O.png");
      static GLuint P = txt::LoadTexture("Textures/Menu/Letters/P.png");
      static GLuint Q = txt::LoadTexture("Textures/Menu/Letters/Q.png");
      static GLuint R = txt::LoadTexture("Textures/Menu/Letters/R.png");
      static GLuint S = txt::LoadTexture("Textures/Menu/Letters/S.png");
      static GLuint T = txt::LoadTexture("Textures/Menu/Letters/T.png");
      static GLuint U = txt::LoadTexture("Textures/Menu/Letters/U.png");
      static GLuint V = txt::LoadTexture("Textures/Menu/Letters/V.png");
      static GLuint W = txt::LoadTexture("Textures/Menu/Letters/W.png");
      static GLuint X = txt::LoadTexture("Textures/Menu/Letters/X.png");
      static GLuint Y = txt::LoadTexture("Textures/Menu/Letters/Y.png");
      static GLuint Z = txt::LoadTexture("Textures/Menu/Letters/Z.png");
      
      static GLuint a = txt::LoadTexture("Textures/Menu/Letters/a.png");
      static GLuint b = txt::LoadTexture("Textures/Menu/Letters/b.png");
      static GLuint c = txt::LoadTexture("Textures/Menu/Letters/c.png");
      static GLuint d = txt::LoadTexture("Textures/Menu/Letters/d.png");
      static GLuint e = txt::LoadTexture("Textures/Menu/Letters/e.png");
      static GLuint f = txt::LoadTexture("Textures/Menu/Letters/f.png");
      static GLuint g = txt::LoadTexture("Textures/Menu/Letters/g.png");
      static GLuint h = txt::LoadTexture("Textures/Menu/Letters/h.png");
      static GLuint i = txt::LoadTexture("Textures/Menu/Letters/i.png");
      static GLuint j = txt::LoadTexture("Textures/Menu/Letters/j.png");
      static GLuint k = txt::LoadTexture("Textures/Menu/Letters/k.png");
      static GLuint l = txt::LoadTexture("Textures/Menu/Letters/l.png");
      static GLuint m = txt::LoadTexture("Textures/Menu/Letters/m.png");
      static GLuint n = txt::LoadTexture("Textures/Menu/Letters/n.png");
      static GLuint o = txt::LoadTexture("Textures/Menu/Letters/o.png");
      static GLuint p = txt::LoadTexture("Textures/Menu/Letters/p.png");
      static GLuint q = txt::LoadTexture("Textures/Menu/Letters/q.png");
      static GLuint r = txt::LoadTexture("Textures/Menu/Letters/r.png");
      static GLuint s = txt::LoadTexture("Textures/Menu/Letters/s.png");
      static GLuint t = txt::LoadTexture("Textures/Menu/Letters/t.png");
      static GLuint u = txt::LoadTexture("Textures/Menu/Letters/u.png");
      static GLuint v = txt::LoadTexture("Textures/Menu/Letters/v.png");
      static GLuint w = txt::LoadTexture("Textures/Menu/Letters/w.png");
      static GLuint x = txt::LoadTexture("Textures/Menu/Letters/x.png");
      static GLuint y = txt::LoadTexture("Textures/Menu/Letters/y.png");
      static GLuint z = txt::LoadTexture("Textures/Menu/Letters/z.png");
      
      switch(letter) {
        case 'A': return A;
        case 'B': return B;
        case 'C': return C;
        case 'D': return D;
        case 'E': return E;
        case 'F': return F;
        case 'G': return G;
        case 'H': return H;
        case 'I': return I;
        case 'J': return J;
        case 'K': return K;
        case 'L': return L;
        case 'M': return M;
        case 'N': return N;
        case 'O': return O;
        case 'P': return P;
        case 'Q': return Q;
        case 'R': return R;
        case 'S': return S;
        case 'T': return T;
        case 'U': return U;
        case 'V': return V;
        case 'W': return W;
        case 'X': return X;
        case 'Y': return Y;
        case 'Z': return Z;

        case 'a': return a;
        case 'b': return b;
        case 'c': return c;
        case 'd': return d;
        case 'e': return e;
        case 'f': return f;
        case 'g': return g;
        case 'h': return h;
        case 'i': return i;
        case 'j': return j;
        case 'k': return k;
        case 'l': return l;
        case 'm': return m;
        case 'n': return n;
        case 'o': return o;
        case 'p': return p;
        case 'q': return q;
        case 'r': return r;
        case 's': return s;
        case 't': return t;
        case 'u': return u;
        case 'v': return v;
        case 'w': return w;
        case 'x': return x;
        case 'y': return y;
        case 'z': return z;
      }   
      return 0;   
    }
    
};

#endif

