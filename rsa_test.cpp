#include"rsa/rsa.hpp"
const int KEY_LEN = 128;
int main()
{
    mpz_t p,q;
    mpz_t n,e,d;
    mpz_t euler;
    mpz_t msg_plain,msg_decrypt,msg_encrypt;
    mpz_t tmp,y_tmp;

    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);
    mpz_init(msg_encrypt);
    mpz_init(msg_decrypt);
    mpz_init(euler);
    mpz_init(tmp);
    mpz_init(y_tmp);
    mpz_init_set_ui(msg_plain,99999);

    createPrimePQ(p,q,KEY_LEN);
    gmp_printf("p,q=%Zd,%Zd\n",p,q);

    mpz_mul(n,p,q);
    gmp_printf("n=p*q=%Zd\n",n);

    getEulerValue(p,q,euler);
    gmp_printf("euler=%Zd\n",euler);

    createPrimeE(e,euler);
    gmp_printf("e=%Zd\n",e);

    get_d(e,euler,tmp,d,y_tmp);
    mpz_add(d,d,euler);
    mpz_mod(d,d,euler);
    gmp_printf("d=%Zd\n",d);

    encrypt(msg_encrypt,msg_plain,e,n);
    gmp_printf("msg_encrypt=%Zd\n",msg_encrypt);

    decrypt(msg_decrypt,msg_encrypt,d,n);
    gmp_printf("msg_decrypt=%Zd\n",msg_decrypt);
    
    return 0;
}