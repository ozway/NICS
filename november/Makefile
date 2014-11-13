default: pdf
	make clean

pdf:
	pdflatex *.tex


clean:
	rm -fv *.log
	rm -fv *.aux
	rm -fv *.toc

cleanpdf:
	rm -fv *.log
	rm -fv *.aux
	rm -fv *.toc
	rm -fv *.pdf


tar: 
	tar czvf ../novemberNICS.tar.gz ../november/*.tex ../november/*.pdf

backup: tar
