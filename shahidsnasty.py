import os
import urllib
import urllib2
def get_mp3(query):
        base_url = 'http://www.translate.google.com/translate_tts?ie=utf-8&tl=en&'
 
        query_data = {'q' :  query}
 
        safe_query = urllib.urlencode(query_data)
        url = base_url + safe_query
 
 
        opener = urllib2.build_opener()
        opener.addheaders = [('User-agent', 'Mozilla/5.0')]
        u = opener.open(url)
 
        # file_name = url.split('/')[-1]
        file_name = str(id(query)) + '.mp3'
        f = open(file_name, 'wb')
        meta = u.info()
        file_size = int(meta.getheaders("Content-Length")[0])
        print "Downloading: %s Bytes: %s" % (file_name, file_size)
 
        file_size_dl = 0
        block_sz = 8192
        while True:
            buffer = u.read(block_sz)
            if not buffer:
                break
 
            file_size_dl += len(buffer)
            f.write(buffer)
            status = r"%10d  [%3.2f%%]" % (file_size_dl, file_size_dl * 100. / file_size)
            status = status + chr(8)*(len(status)+1)
            print status,
 
        f.close()
        return file_name
 
# get_mp3("a"*100)     
def split_raw_string(raw_string):
        # clean up string
        import re
        clean_string = re.sub(' +',' ', raw_string)
        tokens = tsplit(clean_string, ('.', '?', '!'))
       
        limit = 75
 
        current_query = ''
 
        all_queries = []
        for token in tokens:
            if len(token) > limit:
                segments = token.split(',')
                for seg in segments:
                    if len(seg) > limit:
                        words = seg.split(' ')
                        current_query = ''
                        for word in words:
                            if len(current_query) > limit:
                                all_queries.append(current_query)
                                current_query = word + ' '
                            else:
                                current_query += word + ' '
                        all_queries.append(current_query)
                    else:    
                        all_queries.append(seg)
            else:
                all_queries.append(token)
 
        return all_queries
 
 
def get_mp3s(big_string):
        queries = split_raw_string(big_string)
        print queries
 
        processed_mp3 = []
        for q in queries:
                mp3_file = get_mp3(q)
                processed_mp3.append(mp3_file)
 
        return processed_mp3
 
def stitch_mp3s(mp3_arr):
        mp3_string = ''
        for filename in mp3_arr:
                mp3_string += filename + ' '
 
        output_file = str(id(mp3_string)) + '_brian.mp3'
       
        import os
        if os.name == "posix":
            total_command = 'cat ' + mp3_string      + ' > ' + output_file
        os.system(total_command)       
 
        for file_name in mp3_arr:
            command = "rm " + file_name
            os.system(command)
       
        return output_file
 
 
def text_to_speech(string):
        mp3_arr = get_mp3s(string)
        return stitch_mp3s(mp3_arr)
        
def tsplit(string, delimiters):
    """Behaves str.split but supports multiple delimiters."""

    delimiters = tuple(delimiters)
    stack = [string,]

    for delimiter in delimiters:
        for i, substring in enumerate(stack):
            substack = substring.split(delimiter)
            stack.pop(i)
            for j, _substring in enumerate(substack):
                stack.insert(i+j, _substring)

    return stack
 
#print text_to_speech(story)