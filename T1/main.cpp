
// allows me to use I/O functions
#include <iostream>
// Allows me to use exception
#include <stdexcept>
// Allows me to use size_t values
#include <cstdint>
// allows me to read a myfile
#include <fstream>
// allows me to use strings

#include <string.h>
#include <cstdlib>
//#include <thread>


/// structures stack
namespace structuresStack {
template<typename T>
class LinkedStack {
public:
    LinkedStack();

    ~LinkedStack();

    void clear(); // limpa pilha

    void push(const T& data); // empilha

    //T pop(); // desempilha
    void pop();

    T& top() const; // dado no topo

    bool empty() const; // pilha vazia

    std::size_t size() const; // tamanho da pilha
    void printStack();
    T& at ();

private:
    class Node {
    public:
        // constructor
        Node(const T& data) {
            data_ = data;
        }
        // constructor
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        // getter: info
        T& data() {
            return data_;
        }

        // getter-constante: info
        const T& data() const {
            return data_;
        }

        // getter: próximo
        Node* next() {
            return next_;
        }
        // getter-constante: próximo
        const Node* next() const {
            return next_;
        }

        // setter: next
        void next(Node* next) {
            next_ = next;
        }
    private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr}; // nodo-topo
    std::size_t size_{0u}; // tamanho
};
// Constructor
/*!

*/
template<typename T>
LinkedStack<T>::LinkedStack() {
}
// Destructor
/*!
    Call the clear method to remove all the elements
*/
template<typename T>
LinkedStack<T>::~LinkedStack() {
    clear();
}

// Clear method
/*!
    First I check if my linked stack is empty, after that i create a new
    pointer to Node to keep the current top of my stack, then I point my
    top_ to the next element (element that is below my top), delete the
    actual top, move my previus pointer to the same of top and decrease
    the size os my stack.
    I do this until my size is equals to zero, which means my
    linked stack is empty
*/
template<typename T>
void LinkedStack<T>::clear() {
    Node* previous = top_;
    while(size_ > 0) {
    top_ = top_->next();
    delete previous;
    previous = top_;
    size_--;
    }
}

// Push method
/*!
    Insert a new element on the top of my stack. First I allocate a new
    element, then this new element next pointer point to the actual top_
    after that I change my top_ pointer to the new element beacause now this
    new element I inserted is my new top
*/
template<typename T>
void LinkedStack<T>::push(const T& data) {
  Node* novo = new Node(data);
  novo->next(top_);
  top_ = novo;
  size_++;
}

// Pop method
/*!
    Gives back the element that is in the top of my stack. Firsts I check
    if my stack us empty or not, then I allocate a new pointer and point
    to the same element that is my actual top_ is pointing, then I move
    my top_ to the next element (the element that is below my top because
    this is a stack) then set the data to the variable I created to return
    the value I want and delete my 'returno' node, because I already took
    it from my stack
*/
// template<typename T>
// T LinkedStack<T>::pop() {
//     T data;
//     if(empty()) {
//        throw std::out_of_range("Empty Linked Stack");
//     }
//     Node* retorno = top_;
//     top_ = top_->next();
//     data = retorno->data();
//     delete retorno;
//     size_--;
//
//     return data;
// }

template<typename T>
void LinkedStack<T>::pop() {
    if(empty()) {
       throw std::out_of_range("Empty Stack pop");
    }
    Node* retorno = top_;
    top_ = top_->next();

    delete retorno;
    size_--;
}

// Top method
/*!
    Just give me the 'data' value of my 'top_' but don't delete the node
*/
template<typename T>
T& LinkedStack<T>::top() const {
    static T data;
    if (empty()) {
        throw std::out_of_range("Empty Stack top");
    } else {
        data = top_->data();
    }
    return data;
}

// Empty method
/*!
    Check if my linked list is empty and return a boolean value
*/
template<typename T>
bool LinkedStack<T>::empty() const {
    return size_ == 0u;
}

// Size method
/*!
    Return the actual size of my linked stack
*/
template<typename T>
std::size_t LinkedStack<T>::size() const {
    return size_;
}

template<typename T>
void LinkedStack<T>::printStack() {

    Node* imprime = top_;
    while(imprime != nullptr) {
      printf("%s\n", imprime->data());
      imprime = imprime->next();
    }
    // printf("%s\n", top_->data());
    // printf("%s\n", imprime->data());

}


template<typename T>
T& LinkedStack<T>::at () {
  return top_->data();
}
}
///} end namespace strucutres


/// namespace queue
namespace structuresQueue {

template<typename T>
// Class LinkedQueue
class LinkedQueue {
public:
    LinkedQueue();

    ~LinkedQueue();

    void clear(); // limpar

    void enqueue(const T& data); // enfilerar

    T dequeue(); // desenfilerar

    T& front() const; // primeiro dado

    T& back() const; // último dado

    bool empty() const; // fila vazia

    std::size_t size() const; // tamanho

    void printQueue();

private:
    class Node {
    public:
        // construtor
        Node(const T& data){
            data_ = data;
        }
        // constructor
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        // getter: info
        T& data() {
            return data_;
        }

        //getter-constante: info
        const T& data() const {
            return data_;
        }

        // getter: next
        Node* next() {
            return next_;
        }

        // getter-constant: next
        const Node* next() const {
            return next_;
        }

        // setter: next
        void next(Node* next) {
            next_ = next;
        }
    private:
        T data_;
        Node* next_{nullptr};
    };

    Node* head{nullptr}; // nodo-cabeça
    Node* tail{nullptr}; // nodo-fim
    std::size_t size_{0u}; // tamanho
};

template<typename T>
LinkedQueue<T>::LinkedQueue() {

}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void LinkedQueue<T>::clear() {
    Node* previous = head;
    while(size_ > 0) {
        head = head->next();
        delete previous;
        previous = head;
        size_--;
    }

}

template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    Node* novo = new Node(data);
    if (size_ == 0) {
        head = novo;
        tail = novo;
        size_++;
    } else {
        tail->next(novo);
        tail = novo;
        size_++;
    }
}

template<typename T>
T LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Empty queue");
    }
    T data;
    Node* leave = head;
    head = head->next();
    data = leave->data();
    delete leave;
    size_--;
    return data;
}

template<typename T>
T& LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Empty queue");
    }

    return head->data();
}

template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Empty queue");
    }
    return tail->data();
}

template<typename T>
bool LinkedQueue<T>::empty() const{
    return size_ == 0;
}

template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return size_;
}

template<typename T>
void LinkedQueue<T>::printQueue() {

    Node* imprime = head;
    while(imprime != nullptr) {
      printf("%d ", imprime->data());
      imprime = imprime->next();
    }
    printf("\n");
    // printf("%s\n", top_->data());
    // printf("%s\n", imprime->data());

}
}
/// end namespaceQueue

using namespace structuresStack;
using namespace structuresQueue;
using namespace std;

// creates a stack of string
auto linked_stack = new LinkedStack<char*>();
//auto linked_queue = new LinkedQueue<char>();
auto linked_queue = new LinkedQueue<int>();
//auto linked_queue_recursao = new LinkedQueue<int>();
// int height = 0;
// int width = 0;

int rotulo = '0';

// funcao matriz componets conexos
void matrizComponentsFunction(int size_x, int size_y, LinkedQueue<int>* arg) {
  int matrizEntrada [size_x][size_y];
  int matrizResultado[size_x][size_y];


  // preenche a matrizResultado com zeros e a matrizEntrada com os valores da lista
  for(int a = 0; a < size_x; a++) {
    for(int b = 0; b < size_y; b++) {
      //matrizEntrada[a][b] = (int)linked_queue->dequeue();
      matrizEntrada[a][b] = linked_queue->dequeue();
      matrizResultado[a][b] = '0';
    }
  }


  // -------imprime as matrizes antes da comparacao--------
  /*!
  for(int c = 0; c < size_x; c++) {
    for(int d = 0; d < size_y; d++) {
      printf("%c", matrizEntrada[c][d]);
    }
    printf("\n");
  }
  printf("\n");

  for(int carro = 0; carro < size_x; carro++) {
    for(int domin = 0; domin < size_y; domin++) {
      printf("%c", matrizResultado[carro][domin]);
    }
    printf("\n");
  }
  */
  //-------------------------------------------------------------

  //comparacao matrizes
  rotulo = '0';
  //*! Cria uma nova lista
  auto linked_queue_recursao = new LinkedQueue<int>();

  // faz a verificacao dos componentes conexos
  for(int a1 = 0; a1 < size_x; a1++) {
    for(int b1 = 0; b1 < size_y; b1++) {

        if(matrizEntrada[a1][b1] == '1') {
          if (matrizResultado[a1][b1] == '0') {

            rotulo = rotulo+1;

            linked_queue_recursao->enqueue(a1);
            linked_queue_recursao->enqueue(b1);

            matrizResultado[a1][b1] = rotulo;

            if(matrizEntrada[a1-1][b1] == '1') {
              if (matrizResultado[a1-1][b1] == '0') {

                linked_queue_recursao->enqueue(a1-1);
                linked_queue_recursao->enqueue(b1);
                matrizResultado[a1-1][b1] = rotulo;


              }
            }

            if(matrizEntrada[a1][b1-1] == '1') {
              if (matrizResultado[a1][b1-1] == '0') {

                linked_queue_recursao->enqueue(a1);
                linked_queue_recursao->enqueue(b1-1);
                matrizResultado[a1][b1-1] = rotulo;

              }
            }

            if(matrizEntrada[a1+1][b1] == '1') {
              if (matrizResultado[a1+1][b1] == '0') {

                linked_queue_recursao->enqueue(a1+1);
                linked_queue_recursao->enqueue(b1);
                matrizResultado[a1+1][b1] = rotulo;

              }
            }

            if(matrizEntrada[a1][b1+1] == '1') {
              if (matrizResultado[a1][b1+1] == '0') {

                linked_queue_recursao->enqueue(a1);
                linked_queue_recursao->enqueue(b1+1);
                matrizResultado[a1][b1+1] = rotulo;

              }
            }

            int x = linked_queue_recursao->dequeue();
            int y = linked_queue_recursao->dequeue();

            while(!linked_queue_recursao->empty()) {
              x = linked_queue_recursao->dequeue();
              y = linked_queue_recursao->dequeue();


                  if(matrizEntrada[x-1][y] == '1') {
                    if (matrizResultado[x-1][y] == '0') {

                      linked_queue_recursao->enqueue(x-1);
                      linked_queue_recursao->enqueue(y);
                      matrizResultado[x-1][y] = rotulo;


                    }
                  }

                  if(matrizEntrada[x][y-1] == '1') {
                    if (matrizResultado[x][y-1] == '0') {

                      linked_queue_recursao->enqueue(x);
                      linked_queue_recursao->enqueue(y-1);
                      matrizResultado[x][y-1] = rotulo;

                    }
                  }

                  if(matrizEntrada[x+1][y] == '1') {
                    if (matrizResultado[x+1][y] == '0') {

                      linked_queue_recursao->enqueue(x+1);
                      linked_queue_recursao->enqueue(y);
                      matrizResultado[x+1][y] = rotulo;

                    }
                  }

                  if(matrizEntrada[x][y+1] == '1') {
                    if (matrizResultado[x][y+1] == '0') {

                      linked_queue_recursao->enqueue(x);
                      linked_queue_recursao->enqueue(y+1);
                      matrizResultado[x][y+1] = rotulo;

                    }
                  }
            }

          }
        }///

    }
  }
  // fim verificacao componentes convexos

  //printf("\n");
  printf("%d\n", (rotulo - 48));
  //printf("\n");

//---------imprime a matriz apos emcontrar componentes------
  /*!
  printf("matriz RES apos comparar: \n\n");
  for(int ca = 0; ca < size_x; ca++) {
    for(int domi = 0; domi < size_y; domi++) {
      printf("%c", matrizResultado[ca][domi]);
    }
    printf("\n");
  }
  */
//----------------------------------------------------

}
// fim funcao matriz components conexos


/// funcao da thread
void matrizValueFuncion(string arg) {
  string xmlfilename = arg;
  ifstream myfile;
  myfile.open(xmlfilename);

  int height = 0; // linhas da matrizEntrada
  int width = 0; // colunas da matrizEntrada

  if (myfile.is_open()) {
    char letter;

    for (int i = 0; !myfile.eof(); i++) {

      myfile.get(letter);

      if (letter == '<') {
        myfile.get(letter); // pega a próxima letra depois do sinal '<'
        if (letter != '/') {
          int j = 0; // variavel para incrementar a posicao do meu vetor char
          char* palavraEmpilha = new char[100];
          while(letter != '>') { // enquanto nao encontrar o meu sinal '>' vai atribuindo os caracteres para o vetor palavraEmpilha
            palavraEmpilha[j] = letter;
            myfile.get(letter); // pega próximo caracter do .xml
            j++; // incrementa indice do vetor palavraEmpilha
          }

          if (strcmp(palavraEmpilha, "height") == 0) {
            int m = 0;
            char* heightValue = new char[5];

            while(letter != '<') {
              myfile.get(letter);
              heightValue[m] = letter;
              m++;
            }

            height = atoi(heightValue);
            //printf("height: %d\n", height);

          } else if (strcmp(palavraEmpilha, "width") == 0) {
            int n = 0;
            char* widthValue = new char[5];

            while(letter != '<') {
              myfile.get(letter);
              widthValue[n] = letter;
              n++;
            }

            width = atoi(widthValue);
            //printf("width: %d\n", width);

          } else if (strcmp(palavraEmpilha, "name") == 0) {
            int o = 0;
            char* nameValue = new char[100];
            myfile.get(letter);
            while(letter != '<') {
              nameValue[o] = letter;
              myfile.get(letter);
              o++;
            }

            printf("%s ", nameValue);

          } else if (strcmp(palavraEmpilha, "data") == 0) {
            linked_queue->clear();

            myfile.get(letter);
            myfile.get(letter);
            while(letter != '<' ) {
              if (letter == '\n') {
                myfile.get(letter);
              } else {

                linked_queue->enqueue(letter);
                myfile.get(letter);
              }
            }

            /*! imprime o tamanho da minha lista de elementos para a matriz*/
            //int size = (int) linked_queue->size();
            //printf("\nSize: %d\n", size );

            // chama a funcao para achar os componentes conexos das imagens
            matrizComponentsFunction(height, width, linked_queue);


          } // fim else if

        } // fim if(letter != '/')
      } // fim if(letter == '<')

    }

    myfile.close();
  } else {
    cout << "Unable to open myfile";
    exit(EXIT_FAILURE);
  }

}
/// end thread matrizValueFuncion

/// thread tags function
void verificarTagsFunction(string arg) {
  string xmlfilename = arg;
  ifstream myfile;

  myfile.open(xmlfilename);
  // if my myfile was open properly I do all the work I have to do
  if (myfile.is_open()) {

    char letter;
    int numberTag = 0; // mostra pra mim o total de tags encontrada

    for (int i = 0; !myfile.eof(); i++) {
      myfile.get(letter);

      if (letter == '<') {
        myfile.get(letter); // pega a próxima letra depois do sinal '<'
        if (letter != '/') {
          int j = 0; // variavel para incrementar a posicao do meu vetor char
          char* palavraEmpilha = new char[100];
          while(letter != '>') { // enquanto nao encontrar o meu sinal '>' vai atribuindo os caracteres para o vetor palavraEmpilha
            palavraEmpilha[j] = letter;
            myfile.get(letter); // pega próximo caracter do .xml
            j++; // incrementa indice do vetor palavraEmpilha
          }

          linked_stack->push(palavraEmpilha);

        } else {

            myfile.get(letter);
            int k = 0;
            char* palavraDesempilha = new char[100];
            while (letter != '>') {
              palavraDesempilha[k] = letter;
              myfile.get(letter);
              k++;
            }
            char* palavraTopoPilha = linked_stack->top();

            /*! se a minha tag for '/' entao verifica se o topo da pilha é igual
            para poder desempilhar */
            if (strcmp(palavraTopoPilha, palavraDesempilha) == 0) {
              linked_stack->pop();
            } else {
              //printf("%s != %s\n\n", palavraTopoPilha, palavraDesempilha);
              //throw std::out_of_range("Invalid tag founded");
              printf("error: closing tag missing\n");
              exit(0);
            }
        }
      }

    }
    //printf("Tamanho pilha: %d\n", (int)linked_stack->size());
    if ((int) linked_stack->size() != 0) {
      //throw std::out_of_range("No empty stack");
      printf("error: tags not closed founded\n");
      exit(0);
    }
    myfile.close();

  } else {
    cout << "Unable to open myfile";
    exit(EXIT_FAILURE);
  }
}
/// end thread tag function


//---------------------////////////--------------------------
int main(int argc, char *argv[]) {

    if (argc < 2 || argc > 2) {
      cout << "Error: expecting -> ./program 'name_file.xml'\n";
    } else {

      // creates a file that will receive my xml file name
      string xmlfilename;
      //std::cin >> xmlfilename;  // entrada
      //xmlfilename = "dataset02.xml";
      xmlfilename = argv[1];
      //std::thread verificarTags(verificarTagsFunction, xmlfilename);
      verificarTagsFunction(xmlfilename);
      //verificarTags.join();
      //std::thread matrizValue(matrizValueFuncion, xmlfilename);
      matrizValueFuncion(xmlfilename);

      //std::cout << xmlfilename << std::endl;  // esta linha deve ser removida
      //matrizValue.join();

    }

    return 0;
}
