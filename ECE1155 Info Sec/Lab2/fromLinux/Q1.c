#include <stdio.h>
#include <openssl/bn.h>


int derivePKey()
{

}
int main()
{

    printf("\n\nTask 1:\n");
    //1a)
    //Let P, q, and e be prime numbers
    BIGNUM *p = BN_new();
    BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");

    BIGNUM *q = BN_new();
    BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");

    BIGNUM *e = BN_new();
    BN_hex2bn(&e, "010001");


    //1b) 
    //Compute the totient of N)
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *one = BN_new();
    BN_hex2bn(&one, "1");
    
    //calculating p-1 and q-1
    BIGNUM *pmin1 = BN_new();
    BN_sub(pmin1, p, one);
    BIGNUM *qmin1 = BN_new();
    BN_sub(qmin1, q, one);

    //calculating totient(N) = (p-1)(q-1)
    BIGNUM *totientN = BN_new();
    BN_mul(totientN, pmin1, qmin1, ctx);
    //printing out totient of N
    char * totientN_str = BN_bn2hex(totientN); 
    printf("1b) The totient of N is: %s\n", totientN_str);


    //1c
    //Check whether the value of e is relatively prime to n 
    BIGNUM *gcd_1c = BN_new();
    BN_gcd(gcd_1c, e, totientN, ctx);
    char * gcd_1c_str = BN_bn2hex(gcd_1c); 
    printf("1c) The GCD of e and totientN is: %s. Therefore it is relatively prime to the totient of N.\n", gcd_1c_str);


    printf("\n\nTask 2:\n");
    //Task 2: Encrypting a Message
    //This is a top secret message! as hex: 4120746f702073656372657421
    //Calculating d
    BIGNUM *M = BN_new();
    BN_hex2bn(&M, "4120746f702073656372657421");
    BIGNUM *d = BN_new();
    BN_mod_inverse(d, e, totientN, ctx);
    //calculating N
    BIGNUM *n = BN_new();
    BN_mul(n, p, q, ctx);
    //C = m^e mod(n)
    BIGNUM *C = BN_new();
    BN_mod_exp(C, M, e, n, ctx);
    char * C_str = BN_bn2hex(C); 
    printf("The message, encrypted, is %s.\n", C_str);

    printf("\n\nTask 3:\n");
    //Task 3: Decrypting A Message
    BIGNUM *M_solved = BN_new();
    BN_mod_exp(M_solved, C, d, n, ctx); 
    char * M_solved_str = BN_bn2hex(M_solved); 
    printf("The message, decrypted, is %s, which matches the original message of 4120746f702073656372657421.\n", M_solved_str);

    printf("\n\nTask 4:\n");
    //Task 4: Signing a message

    //Original message $2000 49206f776520796f752024323030302e
    //Original message $7000 49206f776520796f752024373030302e
    BIGNUM *M41 = BN_new();
    BN_hex2bn(&M41, "49206f776520796f752024323030302e");
    BIGNUM *C4 = BN_new();
    BN_mod_exp(C4, M41, d, n, ctx);
    char * C_str41 = BN_bn2hex(C4); 
    printf("The message saying $2000, signed, is %s.\n", C_str41);

    BN_hex2bn(&M41, "49206f776520796f752024373030302e");
    BN_mod_exp(C4, M41, d, n, ctx);
    char * C_str42 = BN_bn2hex(C4); 
    printf("The message saying $7000, signed, is %s.\n", C_str42);


    printf("\n\nTask 5:\n");
    //Task 5
    //Launch a missile. in hex is 4c61756e63682061206d697373696c652e
    //the s that came in 643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F
    //010001 hex value
    //n: AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115
    BIGNUM *n5 = BN_new();
    BN_hex2bn(&n5, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");
    BIGNUM *s5 = BN_new();
    BN_hex2bn(&s5, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");
    BIGNUM *e5 = BN_new();
    BN_hex2bn(&e5, "010001");
    BIGNUM *M5 = BN_new();
    BN_mod_exp(M5, s5, e5, n5, ctx);
    char * M5_str = BN_bn2hex(M5); 
    printf("The message, verified, is %s, which matches the original message of 4c61756e63682061206d697373696c652e.\n", M5_str);

    BIGNUM *s5_bad = BN_new();
    BN_hex2bn(&s5_bad, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F");
    BIGNUM *M5_bad = BN_new();
    BN_mod_exp(M5_bad, s5_bad, e5, n5, ctx);
    char * M5_str_bad = BN_bn2hex(M5_bad); 
    printf("If we corrupt even one bit in the signature, the computed message is %s, which no longer matches the initial message.\n", M5_str_bad);



    return 1;
}