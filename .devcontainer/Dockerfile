FROM fedora:latest

# Install required packages
RUN dnf install -y \
    git \
    vim \
    gcc \
    g++ \
    gdb \
    clang \
    clang-tools-extra \
    tree \
    btop \
    lldb \
    make \
    curl \
    nano \
    vim \
    bash \
    zsh \
    valgrind \
    eza \
    tmux \
    qt6-qtbase-devel \
    qt6-qttools-devel \ 
    qt6-qtcreator \
    doxygen \
    graphviz \
    --skip-unavailable

RUN dnf update -y && dnf clean all

# Copy your project files into the container
WORKDIR /app
COPY . /app

# Clone missing directories if needed
RUN if [ ! -d src/webservice/crow ] || [ -z "$(ls -A src/webservice/crow)" ]; then \
      echo "Cloning crow repository..."; \
      git clone --recursive https://github.com/crowcpp/crow.git src/webservice/crow; \
    else \
      echo "src/webservice/crow is not empty, skipping clone"; \
    fi && \
    if [ ! -d src/webservice/asio ] || [ -z "$(ls -A src/webservice/asio)" ]; then \
      echo "Cloning asio repository..."; \
      git clone --recursive https://github.com/chriskohlhoff/asio.git src/webservice/asio; \
    else \
      echo "src/webservice/asio is not empty, skipping clone"; \
    fi

# Install Oh My Zsh (non-interactive)
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended

# Install Oh My Zsh plugins
RUN git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-autosuggestions && \
    git clone https://github.com/zdharma-continuum/fast-syntax-highlighting.git ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/fast-syntax-highlighting && \
    git clone https://github.com/zsh-users/zsh-completions ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-completions

# Configure .zshrc with necessary plugins
RUN echo 'export ZSH="$HOME/.oh-my-zsh"' > /root/.zshrc && \
    echo 'ZSH_THEME="amuse"' >> /root/.zshrc && \
    echo 'plugins=(git zsh-autosuggestions fast-syntax-highlighting zsh-completions)' >> /root/.zshrc && \
    echo 'source $ZSH/oh-my-zsh.sh' >> /root/.zshrc && \
    echo 'alias ls="eza"' >> /root/.zshrc && \
    echo 'alias sl="command ls"' >> /root/.zshrc

# Change default shell for root to zsh
RUN chsh -s /bin/zsh root

# Hardcode timezone to PST (America/Los_Angeles)
RUN ln -sf /usr/share/zoneinfo/America/Los_Angeles /etc/localtime && \
    echo "America/Los_Angeles" > /etc/timezone

# Use zsh as the default shell for RUN commands
SHELL ["/bin/zsh", "-c"]

# Start an interactive zsh shell by default
CMD ["zsh"]
