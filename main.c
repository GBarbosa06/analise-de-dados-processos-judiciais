#include "processo.h"

int main() {
    Processo processos[20000];
    int n = carregarProcessos("processo_043_202409032338.csv", processos, 20000);
    if (n <= 0) {
        printf("Erro ao carregar os processos.\n");
        return -1;
    }
   
    printf("Total de processos carregados: %d\n", n);
    int escolha = 0;
    printf("Escolha uma opcao:\n");
    printf("1. Ordenar por ID (crescente)\n");
    printf("2. Ordenar por data (decrescente)\n");
    printf("3. Contar por classe\n");
    printf("4. Identificar quantos assuntos constam\n");
    printf("5. Listar processos que estao vinculados a mais de um assunto\n");
    printf("6. Calcular dias tramitando\n");
    printf("7. Sair\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            ordenarPorId(processos, 0, n - 1);
            salvarOrdenadoPorId("processos_ordenados_por_id.csv", processos, n);
            printf("Processos ordenados por ID. Novo arquivo criado\n");
            break; 
        
        case 2:
            ordenarPorData(processos, 0, n - 1); 
            salvarOrdenadoPorData("processos_ordenados_por_data.csv", processos, n); 
            printf("Processos ordenados por data. Novo arquivo criado\n");
            break;
            
        case 3:
        {
            char id_classe[10];
            printf("Digite o id_classe que deseja buscar: ");
            scanf("%s", id_classe);
            int quantidade = contarPorClasse(processos, n, id_classe);
            printf("Total de processos com id_classe %s: %d\n", id_classe, quantidade);
            break;
        }
        case 4:
        {
            int total_assuntos = contarAssuntosUnicos(processos, n);
            printf("Total de assuntos unicos: %d\n", total_assuntos);
            break;
        }
        case 5:
            listarMultiplosAssuntos(processos, n);
            break;
        case 6:
        {
            int id_procurado;
            char data_atual[11];
            printf("Digite a data atual (dd/mm/aaaa): ");
            scanf("%s", data_atual);

            // Validar formato da data
            int dia, mes, ano;
            if (sscanf(data_atual, "%d/%d/%d", &dia, &mes, &ano) != 3) {
                printf("Erro: formato de data inválido. Use dd/mm/aaaa.\n");
                break;
            }

            printf("Deseja consultar por ID ou deseja ver todos os processos? (1 para ID, 2 para todos): ");
            int opcao;
            scanf("%d", &opcao);

            if (opcao == 2) {
                printf("Processos em tramitação:\n");
                for (int i = 0; i < n; i++) {
                    int dias = calcularDiasTramitando(processos[i].data_ajuizamento, data_atual);
                    printf("Processo ID %d está em tramitação há %d dias.\n", processos[i].id, dias);
                }
                break;
            }

            if (opcao != 1) {
                printf("Opcao invalida. Escolha 1 para consultar por ID ou 2 para consultar todos os processos.\n");
                break;
            }

            printf("Digite o ID do processo que deseja consultar: ");
            scanf("%d", &id_procurado);

            int encontrado = 0;
            for (int i = 0; i < n; i++) {
                if (processos[i].id == id_procurado) {
                    int dias = calcularDiasTramitando(processos[i].data_ajuizamento, data_atual);
                    printf("Processo ID %d esta em tramitacao ha %d dias.\n", processos[i].id, dias);
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado) {
                printf("Processo com ID %d nao encontrado.\n", id_procurado);
            }
            break;
        }
        case 7:
            printf("Saindo...\n");
            return 0;
    
        default:
            break;
    }
        return 0;
}
