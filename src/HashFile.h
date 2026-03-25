#ifndef HASHFILE_H
#define HASHFILE_H

#include <stdio.h>

//Estrutura arquivo hash
typedef struct HashFile HashFile;

/** Cria um arquivo hash
 * @param filename Nome do arquivo
 * @return Ponteiro para HashFile ou NULL quando erro
 */
HashFile* createFile(const char* filename);


/** Abre um arquivo hash existente
 * @param filename Nome do arquivo
 * @return Ponteiro para HashFile/NULL
 */
HashFile* openFile(const char* filename);

/** Insere um registro
 * @param file Estrutura do arquivo
 * @param key Chave
 * @param value Valor
 * @return 0 = sucesso, -1= erro
 */
int insertRegister(HashFile* file, int key, int value);


/** Busca um registro
 * @param file Estrutura do arquivo
 * @param key Chave
 * @param value Ponteiro para retorno
 * @return 0 = encontrado, -1 = não encontrado
 */
int searchRegister(HashFile* file, int key, int* value);

/** Remove um registro
 * @param file Estrutura hash
 * @param key Chave
 * @return 0 = sucesso, -1 = erro
 */
int removeRegister(HashFile* file, int key);

/** Fecha o arquivo
 * @param file Estrutura
 */
void closeFile(HashFile* file);

#endif 
