FROM fedora:latest

# Install required packages
RUN dnf install -y \
    git \
    gh \
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
    bash \
    zsh \
    valgrind \
    tmux \
    qt6-qtbase-devel \
    qt6-qttools-devel \
    qt6-qtcreator \
    doxygen \
    graphviz \
    gawk \
    cargo \
    tzdata \
    --skip-unavailable && \
    dnf clean all

# Add Cargo bin to PATH early in case it’s needed later
ENV PATH="/root/.cargo/bin:${PATH}"

# Install eza via Cargo
RUN cargo install eza

# Set working directory
WORKDIR /app

# Copy project files
COPY . /app

# Clone crow and asio if missing
RUN [ ! -d src/webservice/crow ] || [ -z "$(ls -A src/webservice/crow)" ] && \
      git clone --recursive https://github.com/crowcpp/crow.git src/webservice/crow || \
      echo "Skipping crow clone" && \
    [ ! -d src/webservice/asio ] || [ -z "$(ls -A src/webservice/asio)" ] && \
      git clone --recursive https://github.com/chriskohlhoff/asio.git src/webservice/asio || \
      echo "Skipping asio clone"

# Install Oh My Zsh (non-interactive)
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended

# Install Zsh plugins
RUN git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-autosuggestions && \
    git clone https://github.com/zdharma-continuum/fast-syntax-highlighting.git ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/fast-syntax-highlighting && \
    git clone https://github.com/zsh-users/zsh-completions ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-completions

# Set up .zshrc
RUN echo 'export ZSH="$HOME/.oh-my-zsh"' > /root/.zshrc && \
    echo 'ZSH_THEME="amuse"' >> /root/.zshrc && \
    echo 'plugins=(git zsh-autosuggestions fast-syntax-highlighting zsh-completions)' >> /root/.zshrc && \
    echo 'source $ZSH/oh-my-zsh.sh' >> /root/.zshrc && \
    echo 'alias ls="eza"' >> /root/.zshrc && \
    echo 'alias sl="command ls"' >> /root/.zshrc

# Change root shell to zsh
RUN chsh -s /bin/zsh root

# Set timezone to PST
RUN ln -sf /usr/share/zoneinfo/America/Los_Angeles /etc/localtime && \
    echo "America/Los_Angeles" > /etc/timezone

# Default shell for container exec
SHELL ["/bin/zsh", "-c"]

# Default entrypoint
CMD ["zsh"]
