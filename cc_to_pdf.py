import os
import sys
import argparse
from pathlib import Path
import tempfile
from fpdf import FPDF
from pygments import highlight
from pygments.lexers import CppLexer
from pygments.formatters import HtmlFormatter
import html
from PyPDF2 import PdfMerger, PdfReader
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, PageBreak, Table, TableStyle
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.pagesizes import letter
from reportlab.lib import colors
from reportlab.lib.units import inch
from reportlab.platypus.flowables import Flowable
import re
from pygments.token import Token
from pygments.lexers import get_lexer_by_name
from reportlab.pdfbase.pdfmetrics import stringWidth

class CodeHighlighter:
    """Classe per processament i formatatge de codi amb syntax highlighting per a PDF"""
    
    def __init__(self):
        self.lexer = get_lexer_by_name("cpp")
        
    def format_for_reportlab(self, code_text):
        """Converteix codi a una llista de paràgrafs amb estil per a ReportLab"""
        # Tokenitzar el codi utilitzant pygments
        tokens = self.lexer.get_tokens(code_text)
        
        # Definir estils per diferents tipus de tokens
        styles = {
            Token.Keyword: ('<font color="#0000FF">', '</font>'),
            Token.Keyword.Type: ('<font color="#008080">', '</font>'),
            Token.Name.Function: ('<font color="#880000">', '</font>'),
            Token.Name.Class: ('<font color="#0000AA">', '</font>'),
            Token.Name.Namespace: ('<font color="#0000AA">', '</font>'),
            Token.String: ('<font color="#008800">', '</font>'),
            Token.String.Char: ('<font color="#008800">', '</font>'),
            Token.Number: ('<font color="#FF0000">', '</font>'),
            Token.Comment: ('<font color="#888888"><i>', '</i></font>'),
            Token.Comment.Multiline: ('<font color="#888888"><i>', '</i></font>'),
            Token.Operator: ('<font color="#666600">', '</font>'),
            Token.Punctuation: ('', ''),
        }
        
        # Processar tokens línia per línia
        lines = []
        current_line = []
        line_num = 1
        
        for ttype, value in tokens:
            if value == '\n':
                # Finalitzar línia actual i afegir-la a la llista de línies
                lines.append((line_num, ''.join(current_line)))
                current_line = []
                line_num += 1
            else:
                # Determinar l'estil per aquest token
                style_start, style_end = '', ''
                for token_type, style in styles.items():
                    if ttype in token_type:
                        style_start, style_end = style
                        break
                
                # Escapar els caràcters HTML
                escaped_value = html.escape(value)
                # Afegir token formatat a la línia actual
                current_line.append(f"{style_start}{escaped_value}{style_end}")
        
        # Afegir l'última línia si hi ha contingut
        if current_line:
            lines.append((line_num, ''.join(current_line)))
        
        # Convertir línies a paràgrafs de Reportlab
        result = []
        for line_num, line in lines:
            # Crear un estil de paràgraf amb font monoespaciada i marge petit
            line_with_num = f'<font color="#999999">{line_num:4d}</font>  {line}'
            result.append(line_with_num)
        
        return result

def find_code_files_recursive(directory):
    """
    Troba recursivament tots els fitxers .cc i .hh en un directori i els seus subdirectoris.
    
    Args:
        directory (str): Directori a explorar
        
    Returns:
        list: Llista de tuples (ruta_relativa, ruta_completa) de tots els fitxers .cc i .hh trobats
    """
    code_files = []
    
    for root, dirs, files in os.walk(directory):
        # Obtenir la ruta relativa des del directori d'origen
        relative_path = os.path.relpath(root, directory)
        
        # Filtrar els fitxers .cc i .hh
        for file in files:
            if file.endswith('.cc') or file.endswith('.hh'):
                # Construir la ruta relativa per al fitxer
                if relative_path == ".":
                    file_relative_path = file
                else:
                    file_relative_path = os.path.join(relative_path, file)
                
                # Construir la ruta completa per al fitxer
                file_full_path = os.path.join(root, file)
                
                code_files.append((file_relative_path, file_full_path))
    
    # Ordenar els fitxers pel camí relatiu
    return sorted(code_files)

# Funció per crear un header amb el link a Mux_Enjoyer
def add_header_with_link(canvas, doc):
    # Desar l'estat actual del canvas
    canvas.saveState()
    
    # Configuració de l'enllaç
    text = "Mux_Enjoyer"
    link = "https://github.com/MUX-enjoyer/PRO2-FIB-2025"
    
    # Posicionar a la cantonada dreta
    pagewidth, pageheight = letter
    text_width = stringWidth(text, "Helvetica", 10)
    x = pagewidth - 72 - text_width  # 72 punts (1 polzada) des de la dreta
    y = pageheight - 36  # 0.5 polzada des de la part superior
    
    # Dibuixar text
    canvas.setFont("Helvetica", 10)
    canvas.setFillColor(colors.blue)
    
    # Afegir l'enllaç
    canvas.linkURL(link, (x-5, y-3, x+text_width+5, y+12), relative=0)
    canvas.drawString(x, y, text)
    
    # Afegir una línia sota el text
    canvas.line(x, y-2, x+text_width, y-2)
    
    # Afegir número de pàgina (excepte per la pàgina d'índex)
    if doc.page > 1:  # Ignorar la primera pàgina (índex)
        canvas.setFont("Helvetica", 9)
        canvas.setFillColor(colors.black)
        canvas.drawString(72, 36, f"Pàgina {doc.page}")
    
    canvas.restoreState()

def get_pdf_page_count(pdf_path):
    """
    Obté el nombre de pàgines d'un fitxer PDF.
    
    Args:
        pdf_path (str): Ruta al fitxer PDF
        
    Returns:
        int: Nombre de pàgines del PDF
    """
    try:
        with open(pdf_path, 'rb') as f:
            pdf = PdfReader(f)
            return len(pdf.pages)
    except Exception as e:
        print(f"Error en llegir el nombre de pàgines de {pdf_path}: {str(e)}")
        return 1  # Si hi ha un error, assumim que el PDF té una pàgina

def create_index_page(code_files, file_page_numbers, source_dir, repo_link):
    """
    Crea els elements per a la pàgina d'índex amb tots els exercicis i fitxers,
    ordenats per número de pàgina.
    
    Args:
        code_files (list): Llista de tuples (ruta_relativa, ruta_completa) dels fitxers
        file_page_numbers (dict): Diccionari amb les pàgines inicials de cada fitxer
        source_dir (str): Ruta al directori d'origen
        repo_link (str): Enllaç al repositori GitHub
        
    Returns:
        list: Llista d'elements reportlab per a la pàgina d'índex
    """
    styles = getSampleStyleSheet()
    
    # Estil per al títol principal
    main_title_style = ParagraphStyle(
        'MainTitle',
        parent=styles['Title'],
        fontSize=20,
        alignment=1,  # Centrat
        spaceAfter=0.4*inch
    )
    
    # Estil per al subtítol (directori d'origen)
    source_dir_style = ParagraphStyle(
        'SourceDir',
        parent=styles['Heading2'],
        fontSize=16,
        alignment=1,  # Centrat
        spaceAfter=0.3*inch
    )
    
    # Estil per al títol de l'índex
    index_title_style = ParagraphStyle(
        'IndexTitle',
        parent=styles['Heading2'],
        fontSize=14,
        alignment=1,  # Centrat
        spaceAfter=0.2*inch
    )
    
    # Estil per als elements de l'índex
    index_item_style = ParagraphStyle(
        'IndexItem',
        parent=styles['Normal'],
        fontSize=11,
        leftIndent=20,
        spaceBefore=3,
        spaceAfter=3
    )
    
    # Elements per al PDF
    elements = []
    
    # Afegir títol principal
    elements.append(Paragraph("JUTGE PRO2 FIB", main_title_style))
    
    # Afegir el nom del directori d'origen
    dir_name = os.path.basename(os.path.normpath(source_dir))
    elements.append(Paragraph(f"{dir_name}", source_dir_style))
    
    # Afegir enllaç al repositori
    repo_style = ParagraphStyle(
        'RepoLink',
        parent=styles['Normal'],
        fontSize=12,
        alignment=1,  # Centrat
        textColor=colors.blue,
        spaceAfter=0.3*inch
    )
    repo_text = f'<a href="{repo_link}" color="blue">GitHub: {repo_link}</a>'
    elements.append(Paragraph(repo_text, repo_style))
    
    # Afegir títol de l'índex
    elements.append(Paragraph("Índex de Fitxers", index_title_style))
    
    # Crear una llista amb totes les entrades ordenades per número de pàgina
    index_entries = []
    
    for file_rel_path, file_full_path in code_files:
        page_num = file_page_numbers.get(file_rel_path, 2)  # Default a pàgina 2 si no es troba
        filename = os.path.basename(file_rel_path)
        folder_path = os.path.dirname(file_rel_path)
        
        # Si el fitxer és d'una subcarpeta, utilitzar el nom de la carpeta com a nom d'exercici
        if folder_path:
            folder_name = os.path.basename(folder_path)
            display_text = f"---- {filename}"
        else:
            display_text = f"<b>{filename}</b>"
        
        index_entries.append((page_num, display_text, folder_path, file_rel_path))
    
    # Ordenar entrades per número de pàgina
    index_entries.sort(key=lambda x: x[0])
    
    # Agrupar per carpeta després d'ordenar per pàgina
    folders_added = set()
    current_folder = None
    
    for page_num, display_text, folder_path, file_rel_path in index_entries:
        # Si canviem de carpeta, afegir un títol de carpeta
        if folder_path and folder_path not in folders_added:
            folder_name = os.path.basename(folder_path)
            folder_style = ParagraphStyle(
                'FolderTitle',
                parent=styles['Heading3'],
                fontSize=12,
                spaceBefore=12,
                spaceAfter=6,
                fontName='Helvetica-Bold'
            )
            elements.append(Paragraph(f"<b>{folder_name}</b>", index_item_style))
            folders_added.add(folder_path)
            current_folder = folder_path
        
        # Afegir l'entrada de l'índex
        elements.append(Paragraph(f"{display_text} (pàgina {page_num})", index_item_style))
    
    # Afegir un salt de pàgina al final
    elements.append(PageBreak())
    
    return elements

def convert_code_to_pdf_recursive(source_dir, dest_dir):
    """
    Converteix recursivament tots els fitxers .cc i .hh d'una carpeta i les seves subcarpetes a PDF amb syntax highlighting,
    els ajunta en un sol PDF i utilitza el nom de la carpeta d'origen com a nom del PDF final.
    
    Args:
        source_dir (str): Ruta a la carpeta que conté els fitxers .cc i .hh
        dest_dir (str): Ruta a la carpeta on es guardarà el PDF generat
    """
    # Assegurar-se que la carpeta de destinació existeix
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)
        print(f"Carpeta de destinació creada: {dest_dir}")
    
    # Obtenir el nom de la carpeta d'origen per utilitzar-lo com a nom del PDF final
    folder_name = os.path.basename(os.path.normpath(source_dir))
    final_pdf_path = os.path.join(dest_dir, f"{folder_name}.pdf")
    
    # Trobar tots els fitxers .cc i .hh de forma recursiva
    code_files = find_code_files_recursive(source_dir)
    
    if not code_files:
        print(f"No s'han trobat fitxers .cc o .hh a {source_dir} ni a les seves subcarpetes")
        return
    
    print(f"S'han trobat {len(code_files)} fitxers .cc i .hh per convertir.")
    
    # Crear una carpeta temporal per a PDFs individuals
    temp_dir = tempfile.mkdtemp()
    pdf_files = []
    file_info = []  # Llista per emmagatzemar (index, file_rel_path, pdf_path)
    
    # Instanciar el resaltador de codi
    highlighter = CodeHighlighter()
    
    # Estils per als paràgrafs
    styles = getSampleStyleSheet()
    
    # Definir estil per al títol
    title_style = ParagraphStyle(
        'TitleStyle',
        parent=styles['Heading1'],
        fontName='Helvetica-Bold',
        fontSize=14,
        alignment=1,  # Centrat
        spaceAfter=20
    )
    
    # Definir estil per al subtítol (nom del fitxer)
    subtitle_style = ParagraphStyle(
        'SubtitleStyle',
        parent=styles['Heading2'],
        fontName='Helvetica',
        fontSize=12,
        alignment=1,  # Centrat
        spaceAfter=10,
        textColor=colors.darkblue
    )
    
    # Definir estil per al codi
    code_style = ParagraphStyle(
        'CodeStyle',
        fontName='Courier',
        fontSize=9,
        leading=10,
        leftIndent=10,
        rightIndent=10
    )
    
    # Enllaç al repositori GitHub
    repo_link = "https://github.com/MUX-enjoyer/PRO2-FIB-2025"
    
    # Primera passada: generar els PDFs individuals i recopilar metadades
    file_page_numbers = {}  # Diccionari per emmagatzemar la pàgina inicial de cada fitxer
    current_page = 2  # Comença a la pàgina 2 (després de l'índex)
    
    # Processa cada fitxer .cc o .hh
    for index, (file_rel_path, file_full_path) in enumerate(code_files):
        temp_pdf_path = os.path.join(temp_dir, f"{index+1:03d}_{Path(file_rel_path).name}.pdf")
        
        try:
            # Llegir el contingut del fitxer
            with open(file_full_path, 'r', encoding='utf-8') as file:
                content = file.read()
            
            # Configurar el document PDF amb la funció de header personalitzada
            doc = SimpleDocTemplate(
                temp_pdf_path,
                pagesize=letter,
                rightMargin=72,
                leftMargin=72,
                topMargin=72,
                bottomMargin=72
            )
            
            # Llista de flowables que aniran al PDF
            elements = []
            
            # Determinar el títol basat en la carpeta
            folder_path = os.path.dirname(file_rel_path)
            filename = os.path.basename(file_rel_path)
            
            # Si el fitxer és d'una subcarpeta, utilitzar el nom de la carpeta com a nom d'exercici
            if folder_path:
                carpeta_nom = os.path.basename(folder_path)
                elements.append(Paragraph(f"Exercici: {carpeta_nom}", title_style))
                # Afegir el nom del fitxer com a subtítol
                elements.append(Paragraph(f"{filename}", subtitle_style))
            else:
                # Si no està en una subcarpeta, utilitzar el nom del fitxer com a exercici
                elements.append(Paragraph(f"Exercici: {filename}", title_style))
            
            elements.append(Spacer(1, 0.2*inch))
            
            # Processar i afegir el codi amb syntax highlighting
            highlighted_lines = highlighter.format_for_reportlab(content)
            
            # Crear un paràgraf pre-formatat per cada línia de codi
            for line in highlighted_lines:
                elements.append(Paragraph(line, code_style))
            
            # Generar el PDF amb el header personalitzat
            doc.build(elements, onFirstPage=add_header_with_link, onLaterPages=add_header_with_link)
            
            # Registra la pàgina inicial d'aquest fitxer
            file_page_numbers[file_rel_path] = current_page
            
            # Obtenir el nombre de pàgines d'aquest PDF i actualitzar el comptador
            page_count = get_pdf_page_count(temp_pdf_path)
            current_page += page_count
            
            # Emmagatzema informació del fitxer per afegir al PDF final
            file_info.append((index+1, file_rel_path, temp_pdf_path))
            
            print(f"Convertit: {file_rel_path} amb realçat de sintaxi ({page_count} pàgines)")
            
        except Exception as e:
            print(f"Error en convertir {file_rel_path}: {str(e)}")
    
    # Ara crea la pàgina d'índex amb les pàgines correctes
    index_pdf_path = os.path.join(temp_dir, "000_index.pdf")
    
    # Crear el document PDF per a l'índex
    doc = SimpleDocTemplate(
        index_pdf_path,
        pagesize=letter,
        rightMargin=72,
        leftMargin=72,
        topMargin=72,
        bottomMargin=72
    )
    
    # Generar els elements per a la pàgina d'índex amb les numeracions de pàgina correctes
    index_elements = create_index_page(code_files, file_page_numbers, source_dir, repo_link)
    
    # Construir la pàgina d'índex
    doc.build(index_elements, onFirstPage=add_header_with_link, onLaterPages=add_header_with_link)
    print("Índex creat amb tots els exercicis i fitxers ordenats per pàgina")
    
    # Ajuntar tots els PDFs en un de sol
    merger = PdfMerger()
    try:
        # Primer afegir l'índex
        if os.path.exists(index_pdf_path):
            merger.append(index_pdf_path)
            print("Índex afegit al PDF final")
        else:
            print(f"Advertència: L'índex {index_pdf_path} no existeix i no s'afegirà al PDF final.")
        
        # Després afegir els fitxers de codi en l'ordre original
        # Ordena els fitxers pel seu índex original per mantenir l'ordre d'inclusió
        file_info.sort(key=lambda x: x[0])
        
        for index, file_rel_path, pdf_path in file_info:
            if os.path.exists(pdf_path):
                merger.append(pdf_path)
                pdf_files.append(pdf_path)  # Afegir a la llista per netejar després
                print(f"Fitxer {index}: {file_rel_path} afegit al PDF final")
            else:
                print(f"Advertència: El fitxer {pdf_path} no existeix i no s'afegirà al PDF final.")
        
        if len(merger.pages) > 0:
            merger.write(final_pdf_path)
            merger.close()
            print(f"PDF final creat: {final_pdf_path}")
        else:
            print("No s'ha pogut crear el PDF final perquè no hi ha pàgines per afegir.")
    except Exception as e:
        print(f"Error al fusionar els PDFs: {str(e)}")
    finally:
        # Netejar els fitxers temporals
        if os.path.exists(index_pdf_path):
            os.remove(index_pdf_path)
        for pdf in pdf_files:
            if os.path.exists(pdf):
                os.remove(pdf)
        os.rmdir(temp_dir)
    
    print("Procés completat!")

def main():
    parser = argparse.ArgumentParser(description='Converteix recursivament fitxers .cc i .hh a PDF amb syntax highlighting')
    parser.add_argument('source_dir', help='Carpeta d\'origen amb fitxers .cc i .hh')
    parser.add_argument('dest_dir', help='Carpeta de destinació per al PDF generat')
    
    args = parser.parse_args()
    
    # Convertir paths a absoluts
    source_dir = os.path.abspath(args.source_dir)
    dest_dir = os.path.abspath(args.dest_dir)
    
    # Verificar que la carpeta d'origen existeix
    if not os.path.exists(source_dir):
        print(f"Error: La carpeta d'origen {source_dir} no existeix.")
        sys.exit(1)
        
    # Executar la conversió
    convert_code_to_pdf_recursive(source_dir, dest_dir)

if __name__ == "__main__":
    main()