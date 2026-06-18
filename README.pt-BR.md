> [!IMPORTANT]
> **Este é um fork não oficial.** Você está vendo o fork pessoal de [**coex177**](https://github.com/coex177), não o projeto oficial. Ele acompanha o upstream e adiciona algumas correções e melhorias de usabilidade (veja [O que muda neste fork](#o-que-muda-neste-fork)). Não é afiliado, apoiado nem endossado pelo autor original.
>
> - **Projeto original:** [BATorrent-app/BATorrent](https://github.com/BATorrent-app/BATorrent), de Mateus Cruz. Use-o para builds oficiais, multiplataforma e assinados (Microsoft Store / Homebrew / AppImage).
> - **Builds deste fork:** [releases do coex177/BATorrent](https://github.com/coex177/BATorrent/releases), atualmente um **alpha só para Windows** (`v4.1.0a`).

<p align="center">
  <a href="README.md">English</a> | <b>Português</b> | <a href="README.zh-CN.md">中文</a> | <a href="README.ja.md">日本語</a> | <a href="README.ru.md">Русский</a> | <a href="README.es.md">Español</a> | <a href="README.de.md">Deutsch</a> | <a href="README.ua.md">Українська</a>
</p>

<p align="center">
  <img src="src/images/logo.svg" alt="BATorrent" width="140">
</p>

<h1 align="center">BATorrent</h1>

<p align="center">
  <i>O cliente BitTorrent com cara — capas de filme, seis temas, zero anúncios.</i>
</p>

<p align="center">
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Fork release" src="https://img.shields.io/github/v/release/coex177/BATorrent?include_prereleases&style=flat-square&color=dc2626&label=fork%20release"></a>
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Downloads" src="https://img.shields.io/github/downloads/coex177/BATorrent/total?style=flat-square&color=dc2626"></a>
  <a href="LICENSE"><img alt="License" src="https://img.shields.io/github/license/coex177/BATorrent?style=flat-square&color=dc2626"></a>
  <img alt="Fork build" src="https://img.shields.io/badge/fork%20build-Windows%20x86__64%20·%20alpha-dc2626?style=flat-square">
</p>

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

<p align="center">
  <img src="src/images/with_startup.gif" alt="BATorrent — abra e use, as capas resolvem sozinhas" width="860">
</p>

A maioria dos clientes de torrent parece uma declaração de imposto de renda. Este aqui mostra seus downloads como uma **parede de capas de filmes, séries e jogos** — a mesma coisa que você reconhece na Netflix ou na Steam — e deixa você vesti-lo com seis temas (ou seu próprio papel de parede). Por baixo do capô é a consagrada engine **libtorrent**, então não é um brinquedo bonitinho: é um cliente de verdade que por acaso tem bom gosto.

> **Sem anúncios. Sem telemetria. Sem versão "Pro". Sem conta.** A única requisição que ele faz sozinho é a checagem de atualização no GitHub, e dá pra desligar. O código está bem aqui — leia o [`updater.cpp`](src/app/updater.cpp) e confira você mesmo.

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## O que muda neste fork

Este fork é baseado no BATorrent original **v4.1.0** e adiciona um conjunto de correções e melhorias de usabilidade. Tudo abaixo desta seção descreve o app original e também se aplica ao fork.

- **Renomear faz o serviço completo.** Renomear um torrent agora atualiza o arquivo ou a pasta no disco *e* o nome mostrado na lista, e a pasta vazia antiga é removida em seguida. Pressione **F2** para renomear; o diálogo foca o campo e aceita no Enter.
- **Remover é confiável.** A exclusão agora trata toda a seleção múltipla (não só o último item clicado), remove a pasta de nível superior do disco quando "também excluir os arquivos" está ligado, e exclui de forma confiável torrents que ainda estão baixando, parando-os primeiro.
- **Preferências reorganizadas.** Uma aba **Downloads** dedicada; campos de caminho editáveis que atualizam após o Procurar; uma opção "Mover arquivos `.torrent` adicionados" e uma opção "Excluir o arquivo `.torrent` após adicionar" (substitui a antiga pasta oculta `.processed`); um botão **Reiniciar** no ícone do app; e um aviso caso a pasta monitorada possa readicionar silenciosamente um torrent que você acabou de remover.
- **Menu da bandeja funcionando no Windows.** O ícone na bandeja do sistema agora tem um menu de clique direito no Windows (Mostrar, Abrir torrent/magnet, Pausar/Retomar tudo, Preferências, Sair).
- **Acabamento.** Diálogos de configurações e de prompt com o tema do app, um diálogo Sobre com botão **Fechar** padrão e uma revisão dos textos em inglês.

> [!NOTE]
> Duas limitações conhecidas deste fork: por enquanto os builds são **só para Windows** (as versões oficiais multiplataforma vêm do upstream), e o atualizador embutido ainda consulta os releases do projeto **original**, então ele não sinaliza as versões deste fork como atualizações.

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## Por que isto existe

*A seção abaixo é do autor original, Mateus Cruz:*

Sou um desenvolvedor sozinho no Brasil. Eu queria um cliente de torrent que levasse privacidade a sério, rodasse nativamente em todo desktop e não parecesse ter sido feito em 2009 — e como não achei nenhum, criei o meu. É grátis e **licenciado sob a MIT**: sem pegadinhas, sem telemetria aparecendo depois e sem poder ser vendido caladinho para uma empresa que enfia anúncios. Oito idiomas, porque "útil" não devia significar "só em inglês".

## O visual

<p align="center">
  <img src="src/images/themes.gif" alt="Alternando entre os temas embutidos" width="860">
</p>

<p align="center">
  <img src="src/images/shot-grid.pt.jpg" alt="Grade de capas" width="860">
</p>

<p align="center">
  <img src="src/images/shot-list.pt.jpg" alt="Visão em lista" width="860">
</p>

<p align="center">
  <img src="src/images/shot-settings.pt.jpg" alt="Preferências" width="860">
</p>

- **Capa automática** — ele lê o nome do torrent e busca o pôster real (filmes e séries via TMDB, jogos via IGDB) numa visão em grade. Um clique alterna para uma lista compacta.
- **Seis temas** — Dark, Light, Midnight, Sakura, Dark Star e um totalmente **Personalizado** (seu próprio fundo + cores de destaque), cada um com arte de destaque anime opcional.
- Gráfico de velocidade em tempo real, progresso colorido por estado, um popup de bandeja rico com velocidades ao vivo e ETA — os detalhes que fazem ele *parecer* acabado.

## O que ele faz de verdade

| | |
|---|---|
| 🔒 **Privacidade em primeiro lugar** | Vínculo à interface da VPN + **kill switch** (corta todo o tráfego se o túnel cair), modo PT para trackers privados, preset Tor, handshake anônimo, bloqueio anti-leecher |
| 🔎 **Achar e adicionar** | Busca embutida (inclui fontes abertas CIS/RuTor, sem login), Colar Inteligente (magnet / `.torrent` / `thunder://` / hash no Ctrl+V), download automático por RSS com filtros regex, arrastar e soltar |
| 📱 **Controle de qualquer lugar** | WebUI no navegador com **pareamento por QR** — escaneie do celular, sem digitar IP. O QR é gerado localmente; seu endereço nunca sai da máquina |
| 📺 **Assistir e organizar** | Assista enquanto baixa, extração automática de arquivos, categorias + tags, atualização da biblioteca Plex/Jellyfin/Emby ao concluir |
| 🔔 **Fique por dentro** | Notificações nativas do desktop, alertas no Telegram, Discord Rich Presence ("Baixando X · 67%") |

<details>
<summary><b>…e a cauda longa</b> (clique para expandir)</summary>

Prioridade por arquivo · download sequencial · injeção automática de trackers · controle de layout de conteúdo · regex de arquivos excluídos · pasta temporária de download · estado Concluído com janelas de seeding · auto-pausa em erro de arquivo · limites globais + por torrent de ratio/tempo · agendador de banda (hora + dia) · importar do qBittorrent · criar arquivos `.torrent` · inspetor de torrent · listas de bloqueio de IP · criptografia de protocolo · mirror de atualização Gitee · desligamento automático ao terminar · exclusão no Windows Defender · backup/restauração completos · histórico de removidos recentemente · forçar início · visualizador de log embutido + diagnósticos + teste de vazamento de IP · formatação por localidade · atalhos de teclado.

</details>

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## Baixar

**Este fork** oferece um único build: um instalador alpha para Windows.

| | | |
|---|---|---|
| **Este fork (Windows)** | [Instalador `v4.1.0a`](https://github.com/coex177/BATorrent/releases/latest) (`BATorrent-setup-x86_64.exe`). Instalação por usuário, sem admin. | Windows 10/11 · x86_64 · **alpha** |

Para builds **oficiais, assinados e multiplataforma**, use o projeto original:

| Plataforma | | |
|---|---|---|
| **Windows** | [Microsoft Store](https://apps.microsoft.com/detail/9n4l3tq24rc6) · [Instalador](https://github.com/BATorrent-app/BATorrent/releases/latest) · [Portátil](https://github.com/BATorrent-app/BATorrent/releases/latest) | Windows 10+ |
| **macOS** | **`brew install --cask Mateuscruz19/batorrent/batorrent`** · [`.dmg`](https://github.com/BATorrent-app/BATorrent/releases/latest) | macOS 12+ · Apple Silicon |
| **Linux** | [AppImage](https://github.com/BATorrent-app/BATorrent/releases/latest) | glibc 2.35+ |

Depois é só arrastar um `.torrent` ou magnet para a janela. Só isso.

<sub>**macOS:** ainda não notarizado (o programa de desenvolvedor da Apple é pago). O Homebrew é o caminho mais suave — o `brew` remove a flag de quarentena, então abre sem o aviso do Gatekeeper. Com o `.dmg`, clique com o botão direito → **Abrir** na primeira vez.</sub>

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

<details>
<summary><b>Compilar do código-fonte e notas de engenharia</b></summary>

### Requisitos
C++17 · CMake 3.16+ · Qt 6 (`Widgets`, `Network`, `Svg`, `Multimedia`) · libtorrent-rasterbar 2.0+ · Boost · Qt6Keychain (opcional).

```bash
# Debian / Ubuntu
sudo apt install build-essential cmake qt6-base-dev qt6-svg-dev qt6-multimedia-dev \
    libtorrent-rasterbar-dev libboost-dev libssl-dev
cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j && ./build/BATorrent
```
(macOS: `brew install qt libtorrent-rasterbar boost openssl`. Windows: instalador do Qt + `vcpkg install libtorrent:x64-windows`.)

### Qualidade e segurança

<p>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml"><img alt="CodeQL" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml/badge.svg"></a>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml"><img alt="Sanitizers" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml/badge.svg"></a>
  <a href="https://sonarcloud.io/summary/new_code?id=Mateuscruz19_BAT-Torrent"><img alt="Quality Gate" src="https://sonarcloud.io/api/project_badges/measure?project=Mateuscruz19_BAT-Torrent&metric=alert_status"></a>
  <a href="https://www.codefactor.io/repository/github/mateuscruz19/batorrent"><img alt="CodeFactor" src="https://www.codefactor.io/repository/github/mateuscruz19/batorrent/badge"></a>
  <a href="https://www.bestpractices.dev/projects/13073"><img alt="OpenSSF Best Practices" src="https://www.bestpractices.dev/projects/13073/badge"></a>
</p>

- **Testes** — suíte Catch2 (unidade, segurança, memória) em todo build de CI; comportamento novo de backend ganha um teste.
- **Sanitizers** — passa limpo sob AddressSanitizer + UndefinedBehaviorSanitizer (0 vazamentos / use-after-free / UB).
- **Revisado** antes de cada release quanto a segurança de memória/threads, autenticação da WebUI, injeção, path traversal, validação de entrada e tratamento de segredos. Segredos ficam no keychain do sistema, nunca em texto puro; a WebUI só abre na rede depois que você define uma senha.

</details>

## Contribuindo

Para problemas **específicos deste fork**, abra issues em [coex177/BATorrent](https://github.com/coex177/BATorrent/issues). Para o app original, use o [repositório upstream](https://github.com/BATorrent-app/BATorrent). Relatos de bug: inclua sua plataforma + versão (`Ajuda → Sobre`) e os passos para reproduzir.

## Licença

[MIT](LICENSE) © 2024–2026 Mateus Cruz (autor original) · feito no Brasil 🦇

Este fork é mantido por [coex177](https://github.com/coex177) e permanece sob a mesma licença MIT.
