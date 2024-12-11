console.log("iniciando o carregamento do script JavaScript");

/*
tipos básicos em JavaScript
- número inteiro ou decimal
- string e caractere
- booleano (true, false)
- função
- lista (array)
- objeto
*/

// fixo para fins didáticos, na realidade viria de um banco de dados
const guerreirix = [
  {
    "nome": "Yuri",
    "curso": "CIC",
    "errouRude": true
  },
  {
    "nome": "David",
    "curso": "ESW",
    "errouRude": true
  },
  {
    "nome": "Andréia",
    "curso": "ESW"
  },
  {
    "nome": "Tiago Alves",
    "curso": "ESW",
    "errouRude": true
  },
  {
    "nome": "Thiago Dellano",
    "curso": "ESW",
    "errouRude": true
  },
  {
    "nome": "Helenna",
    "curso": "ESW",
    "errouRude": true
  },
  {
    "nome": "Allan",
    "curso": "CIC",
    "errouRude": true
  },
  {
    "nome": "Guilherme",
    "curso": "CIC"
  },
  {
    "nome": "Davi",
    "curso": "CIC",
    "errouRude": true
  },
  {
    "nome": "Samuel",
    "curso": "ESW",
    "errouRude": true
  },
  {
    "nome": "Gabriel Braga",
    "curso": "ESW",
    "errouRude": true
  },
  {
    "nome": "Gabriel Delforge",
    "curso": "ESW",
    "errouRude": true
  },
  {
    "nome": "Kayke",
    "curso": "ESW",
    "errouRude": true
  },
  {
    "nome": "Bruno",
    "curso": "ESW"
  },
  {
    "nome": "Murilo",
    "curso": "CIC"
  },
  {
    "nome": "Marcelo Mello"
  },
  {
    "nome": "Marcelo Nascimento"
  },
  {
    "nome": "Rafael"
  },
  {
    "nome": "Enzo"
  },
  {
    "nome": "Pedro",
    "curso": "CIC",
    "errouRude": true
  },
  {
    "nome": "João Genaro",
    "curso": "ESW",
    "errouRude": true
  },
  {
    "nome": "Lucas Martins"
  },
];

function sortGuerreirix(g1, g2) {
  return g1.nome.localeCompare(g2.nome);
}

function imprimir_pessoas(Ordem) {
  // 1. limpar a lista de pessoas do UL
  const listaGuerreirix = document.getElementById("listaDeGuerreirix");
  while (listaGuerreirix.firstChild) {
    listaGuerreirix.removeChild(listaGuerreirix.lastChild);
  }

  // 2. alterar a ordem das pessoas
  var copiaGuerreirix = guerreirix.map((x) => x); // cópia para evitar alterar o original
  switch (Ordem) {
    case "Crescente": console.log("executando a listagem de guerreirix em ordem Crescente");
                      copiaGuerreirix.sort(sortGuerreirix); break;
    case "Decrescente": console.log("executando a listagem de guerreirix em ordem Decrescente");
                        copiaGuerreirix.sort(sortGuerreirix).reverse(); break;
    case "CIC": console.log("executando a listagem de guerreirix de CIC");
                copiaGuerreirix = guerreirix.filter((guerr) => guerr.curso === "CIC"); break;
    case "ESW": console.log("executando a listagem de guerreirix de ESW");
                copiaGuerreirix = guerreirix.filter((guerr) => guerr.curso === "ESW"); break;
    case "Errou rude": console.log("executando a listagem de pessoas (não-guerreirix) que erraram rude");
                         copiaGuerreirix = guerreirix.filter((guerr) => guerr.errouRude === true); break;
    default: console.log("executando a listagem de todix guerreirix");
  }

  // 3. inserir a lista de pessoas no UL
  const destacarCurso = document.getElementById("destacar-curso");
  for (let i = 0; i < copiaGuerreirix.length; i++) {
    const novoItem = document.createElement("li");
    if (destacarCurso.checked) {
      if (copiaGuerreirix[i].curso === "CIC") {
        novoItem.classList.add("cic");
      } else if (copiaGuerreirix[i].curso === "ESW") {
        novoItem.classList.add("esw");
      }
    }
    novoItem.innerHTML = copiaGuerreirix[i].nome;
    listaGuerreirix.appendChild(novoItem);
  }

  // 4. atualizar o parágrafo com a quantidade de pessoas
  const paragrafoTotal = document.getElementById("quantidade");
  paragrafoTotal.textContent = "Somos " + copiaGuerreirix.length + " guerreirix!";
}

function experimentos_pega_no_dom() {
  console.log("executando exemplos de manipulação do DOM")

  const painelMutante = document.getElementById("mutante");

  // por ID
  const errouRude = document.getElementById("h1");
  console.log(errouRude)
  errouRude.innerHTML = errouRude.innerHTML + " - FALTOU";
  errouRude.remove();

  // por TAG
  const itens = document.getElementsByTagName("li");
  console.log(itens)
  painelMutante.innerHTML = itens;

  // por CLASSE
  const pessoas = document.getElementsByClassName("cic");
  console.log(pessoas)
  painelMutante.innerHTML = "<ol>";
  for (let i = 0; i < pessoas.length; i++) {
    painelMutante.innerHTML += "<li>" + pessoas[i].innerHTML + "</li>";
  }
  painelMutante.innerHTML += "</ol>";

  const novaLista = document.createElement("ol");
  for (let i = 0; i < pessoas.length; i++) {
    const novoItem = document.createElement("li");
    novoItem.innerHTML = pessoas[i].innerHTML;
    painelMutante.appendChild(novoItem);
  }
  // painelMutante.innerHTML = "";
  painelMutante.appendChild(novaLista);

}

console.log("terminando o carregamento do script JavaScript");