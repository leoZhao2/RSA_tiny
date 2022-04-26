#include"rsa.h"

void getEulerValue(mpz_t &p, mpz_t &q, mpz_t &euler)
{
	mpz_t p_tmp, q_tmp, tmp;

	mpz_init(p_tmp);
	mpz_init(q_tmp);
	mpz_init(tmp);

	mpz_init_set_ui(tmp, 1);

	mpz_sub(p_tmp, p, tmp);
	mpz_sub(q_tmp, q, tmp);

	mpz_mul(euler, p_tmp, q_tmp);

	mpz_clear(p_tmp);
	mpz_clear(q_tmp);
	mpz_clear(tmp);
}
void createPrimePQ(mpz_t &rand_p, mpz_t &rand_q, const int MAX_BITS)
{
	unsigned long rand_seed = time(nullptr);

	gmp_randstate_t state;
	gmp_randinit_default(state);

	gmp_randseed_ui(state, rand_seed);

	mpz_urandomb(rand_p, state, MAX_BITS);
	while (!mpz_probab_prime_p(rand_p, 15))
	{
		mpz_urandomb(rand_p, state, MAX_BITS);
	};
	mpz_nextprime(rand_q, rand_p);
}
void createPrimeE(mpz_t &e, mpz_t euler)
{
	unsigned long rand_seed = time(nullptr);
	mpz_t tmp, cons_one;

	mpz_init_set_ui(tmp, 2); // tmp != 1
	mpz_init_set_ui(cons_one, 1);

	gmp_randstate_t state;
	gmp_randinit_default(state);

	gmp_randseed_ui(state, rand_seed);

	while (mpz_cmp(tmp, cons_one))
	{
		mpz_urandomm(e, state, euler);
		mpz_gcd(tmp, e, euler);
	}
	mpz_clear(tmp);
	mpz_clear(cons_one);
}
void encrypt(mpz_t &ciphertext, mpz_t &plaintext, mpz_t &e, mpz_t &n)
{
	mpz_t i, j, k, l;
	mpz_init_set_ui(i, 2);
	mpz_init_set_ui(j, 1);
	mpz_init_set_ui(l, 0);
	mpz_init(k);
	mpz_set(ciphertext, j);
	mpz_mod(plaintext, plaintext, n);
	while (mpz_cmp(e, l) > 0)
	{
		if (mpz_odd_p(e))
		{
			mpz_mul(ciphertext, ciphertext, plaintext);
			mpz_mod(ciphertext, ciphertext, n);
		}
		mpz_div(e, e, i);
		mpz_mul(plaintext, plaintext, plaintext);
		mpz_mod(plaintext, plaintext, n);
	}
	mpz_clear(i);
	mpz_clear(j);
	mpz_clear(k);
	mpz_clear(l);
}
void decrypt(mpz_t &plaintext, mpz_t &ciphertext, mpz_t &d, mpz_t &n)
{
	mpz_t i, j, k, l;
	mpz_init_set_ui(i, 2);
	mpz_init_set_ui(j, 1);
	mpz_init_set_ui(l, 0);
	mpz_init(k);
	mpz_set(plaintext, j);
	mpz_mod(ciphertext, ciphertext, n);
	while (mpz_cmp(d, l) > 0)
	{
		if (mpz_odd_p(d))
		{
			mpz_mul(plaintext, plaintext, ciphertext);
			mpz_mod(plaintext, plaintext, n);
		}
		mpz_div(d, d, i);
		mpz_mul(ciphertext, ciphertext, ciphertext);
		mpz_mod(ciphertext, ciphertext, n);
	}
	mpz_clear(i);
	mpz_clear(j);
	mpz_clear(k);
	mpz_clear(l);
}
void get_d(mpz_t &e, mpz_t &euler, mpz_t &tmp, mpz_t &a, mpz_t &b)
{
	mpz_t cons_zero, cons_one, i;
	mpz_init_set_ui(cons_zero, 0);
	mpz_init_set_ui(cons_one, 1);
	mpz_init(i);
	if (mpz_cmp(cons_zero, euler) == 0)
	{
		mpz_set(tmp, e);
		mpz_set(a, cons_one);
		mpz_set(b, cons_zero);
		return;
	}
	mpz_mod(i, e, euler);
	get_d(euler, i, tmp, b, a);
	mpz_div(i, e, euler);
	mpz_mul(i, i, a);
	mpz_sub(b, b, i);
	mpz_clear(cons_zero);
	mpz_clear(cons_one);
	mpz_clear(i);
}
void rsa_test(int KEY_LEN)
{
    mpz_t p, q;
    mpz_t n, e, d;
    mpz_t euler;
    mpz_t msg_plain, msg_decrypt, msg_encrypt;
    mpz_t tmp, y_tmp;

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
    mpz_init_set_ui(msg_plain, 99999);

    createPrimePQ(p, q, KEY_LEN);
    gmp_printf("p,q=%Zd,%Zd\n", p, q);

    mpz_mul(n, p, q);
    gmp_printf("n=p*q=%Zd\n", n);

    getEulerValue(p, q, euler);
    gmp_printf("euler=%Zd\n", euler);

    createPrimeE(e, euler);
    gmp_printf("e=%Zd\n", e);

    get_d(e, euler, tmp, d, y_tmp);
    mpz_add(d, d, euler);
    mpz_mod(d, d, euler);
    gmp_printf("d=%Zd\n", d);

    encrypt(msg_encrypt, msg_plain, e, n);
    gmp_printf("msg_encrypt=%Zd\n", msg_encrypt);

    decrypt(msg_decrypt, msg_encrypt, d, n);
    gmp_printf("msg_decrypt=%Zd\n", msg_decrypt);

}
void rsa_create(mpz_t &r_e,mpz_t &r_n,mpz_t &r_d,int KEY_LEN){
    mpz_t p, q;
    mpz_t n, e, d;
    mpz_t euler;
    mpz_t msg_plain, msg_decrypt, msg_encrypt;
    mpz_t tmp, y_tmp;

    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);
    mpz_init(euler);
    mpz_init(tmp);
    mpz_init(y_tmp);


    createPrimePQ(p, q, KEY_LEN);
    mpz_mul(n, p, q);
    getEulerValue(p, q, euler);
    createPrimeE(e, euler);
    get_d(e, euler, tmp, d, y_tmp);
    mpz_add(d, d, euler);
    mpz_mod(d, d, euler);
    mpz_set(r_e,e);
    mpz_set(r_n,n);
    mpz_set(r_d,d);
}