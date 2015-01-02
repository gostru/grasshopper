/***********************************************************************************/
/* Implementation of Gost Grasshopper Encryption Algorithm                         */
/* This program implements the test vectors set provided in the reference document */
/* provided by the Standartinform, Moscow, Russian Federation.                     */
/*                                                                                 */
/* Author: Eric Filiol                                                             */
/* This program is protected by the GPLv3                                          */
/***********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "gost_grasshopper.h"

int main()
 {
  unsigned long int bloctest[2], mkey[4], * * subkeys, plaintext[2], ciphertext[2];
  unsigned char i;

  /* Allocation of subkey array      */
  subkeys = (unsigned long int * *)calloc(10, sizeof(unsigned long int *));
  for(i = 0;i < 10;i++) subkeys[i] = (unsigned long int *)calloc(2, sizeof(unsigned long int));
   
  /* The master key provided in the reference document */
  mkey[0] = 0x8899aabbccddeeffLL;
  mkey[1] = 0x0011223344556677LL;
  mkey[2] = 0xfedcba9876543210LL;
  mkey[3] = 0x0123456789abcdefLL;

  printf("%016lx%016lx%016lx%016lx\n", mkey[0], mkey[1], mkey[2], mkey[3]);
  /* Key setup procedure */
  key_setup(mkey, subkeys);

  /* Plaintext provided by the reference document      */
  plaintext[0] = 0x1122334455667700LL;
  plaintext[1] = 0xffeeddccbbaa9988LL;
 
  printf("Plaintext = %016lx%016lx\n", plaintext[0], plaintext[1]);
  
  /* Encryption procedure call                         */
  grasshopper_encrypt(subkeys, plaintext, ciphertext);
  printf("Ciphertext = %016lx%016lx\n", ciphertext[0], ciphertext[1]);
  
  /* Decryption procedure call                         */
  grasshopper_decrypt(subkeys, ciphertext, plaintext);
  printf("Plaintext = %016lx%016lx\n", plaintext[0], plaintext[1]);
  
  /* Free subkey array                                 */
  for(i = 0;i < 10;i++) free(subkeys[i]);
  free(subkeys);
 }
