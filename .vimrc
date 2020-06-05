command! MakeTags :AsyncRun ctags -f .tags -R --exclude='*.json' .

" set makeprg=make
nnoremap <F4> :AsyncRun g++ main.cpp -o main -std=c++11 -Iinclude/ && ./main Seq\ input.ipynb<cr>
