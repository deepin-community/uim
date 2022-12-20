#!/usr/bin/env ruby
#===========================================================================
#  Filename : check_declare_func_typo.rb
#
#  Copyright (C) 2005-2006 Kazuki Ohta <mover at hct.zaq.ne.jp>
#  Copyright (c) 2007-2008 SigScheme Project <uim-en AT googlegroups.com>
#
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. Neither the name of authors nor the names of its contributors
#     may be used to endorse or promote products derived from this software
#     without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
#  IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
#  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#===========================================================================
$orig_info     = {}
$declare_info  = {}
$orig_info2    = {}
$declare_info2 = {}

############################################################################
# Pickup raw Scm_Register* 
############################################################################

def build_orig_info
  files = ["sigscheme.c", "operations-srfi1.c",
           "operations-srfi2.c", "operations-srfi6.c", "operations-srfi8.c", 
           "operations-srfi23.c", "operations-srfi34.c", "operations-srfi38.c",
           "operations-srfi60.c", "operations-siod.c"]

  files.each { |file|
    IO.readlines(file).each { |line|
      if (!line.include?("\""))
        next
      end

      if (/Scm_Register(Procedure|Syntax)*\(*/ =~ line.split("\"")[0])
        regfunc = line.split("\"")[0].strip[0..-2]
        scmname = line.split("\"")[1].strip


        $orig_info[scmname] = regfunc
        $orig_info2[regfunc] = scmname
      end
    }
  }
end

############################################################################
# Pickup DECLARE_FUNCTION
############################################################################
FUNC_TYPE_INVALID   = 0
FUNC_TYPE_SYNTAX    = 1
FUNC_TYPE_PROCEDURE = 2
FUNC_TYPE_REDUCTION = 3

TYPE2PREFIX = {
  FUNC_TYPE_SYNTAX    => "ScmExp",
  FUNC_TYPE_PROCEDURE => "ScmOp",
  FUNC_TYPE_REDUCTION => "ScmOp",
}

SCM2C_FUNCNAME_RULE = [
  # prefix
  [/^\+/,        "add"],
  [/^\*/,        "multiply"],
  [/^-/,         "subtract"],
  [/^\//,        "divide"],
  [/^<=/,         "less_eq"],
  [/^</,          "less"],
  [/^>=/,         "greater_eq"],
  [/^>/,          "greater"],
  [/^\=/,         "equal"],
  [/^%%/,         "sscm_"],

  # suffix
  [/\?$/,  "p"],
  [/!$/,   "d"],

  # suffix or intermediate
  [/->/,  "2"],
  [/-/,   "_"],
  [/\?/,  "_"],
  [/!/,   "_"],
  [/\=/,  "equal"],
  [/\*/,  "star"],
  [/\+/,  "plus"],
]

def guess_c_funcname(prefix, scm_funcname, type)
  # guess prefix
  c_prefix = TYPE2PREFIX[type] || "";
  if (prefix.length != 0)
    c_prefix += prefix
  else
    c_prefix += "_"
  end

  # apply replace rule
  c_funcname = scm_funcname
  SCM2C_FUNCNAME_RULE.each { |rule|
    c_funcname = c_funcname.gsub(rule[0], rule[1])
  }
  
  return c_prefix + c_funcname
end

def search_declare_function(prefix, filename)
#  puts "    /* #{filename} */"
  IO.readlines(filename).each{ |line|
    if line.strip =~ /DECLARE_FUNCTION\(\"(\S+)\",\s*((Syntax|Procedure|Reduction)\S+)\);/
      scm_func = $1
      reg_func = "Scm_Register" + $2

      type = if reg_func.index("Syntax")
               FUNC_TYPE_SYNTAX
             elsif reg_func.index("Procedure")
               FUNC_TYPE_PROCEDURE
             elsif reg_func.index("Reduction")
               FUNC_TYPE_REDUCTION
             else
               FUNC_TYPE_INVALID
             end

      c_func = guess_c_funcname(prefix, scm_func, type)

      $declare_info[scm_func] = reg_func;
      $declare_info2[reg_func] = scm_func;

#      puts "    { \"#{scm_func}\", (ScmFuncType)#{c_func}, (ScmRegisterFunc)#{reg_func} },"
    end
  }
end

def build_table(prefix, filename)
  search_declare_function(prefix, filename)
end

def null_entry()
#  puts "    {NULL, NULL, NULL}"
end

def print_tableheader(tablename)
#  puts "struct builtin_func_info #{tablename}[] = {"
end

def print_tablefooter()
#  puts "};"
#  puts ""
end

def build_functable(prefix, tablename, filelist)
  print_tableheader(tablename)
  filelist.each { |filename|
    build_table(prefix, filename)
  }
  null_entry()
  print_tablefooter
end

def print_header()
  IO.readlines("./script/functable-header.txt").each { |line|
#    puts line
  }
end

def print_footer()
  IO.readlines("script/functable-footer.txt").each { |line|
#    puts line
  }
end

######################################################################

# Header
print_header

# R5RS
build_functable("",
                "r5rs_func_info_table",
                ["eval.c", "io.c", "operations.c", "sigscheme.c"])

# SRFI-1
build_functable("_SRFI1_",
                "srfi1_func_info_table",
                ["operations-srfi1.c"])

# SRFI-2
build_functable("_SRFI2_",
                "srfi2_func_info_table",
                ["operations-srfi2.c"])

# SRFI-6
build_functable("_SRFI6_",
                "srfi6_func_info_table",
                ["operations-srfi6.c"])

# SRFI-8
build_functable("_SRFI8_",
                "srfi8_func_info_table",
                ["operations-srfi8.c"])

# SRFI-23
build_functable("_SRFI23_",
                "srfi23_func_info_table",
                ["operations-srfi23.c"])

# SRFI-34
build_functable("_SRFI34_",
                "srfi34_func_info_table",
                ["operations-srfi34.c"])

# SRFI-38
build_functable("_SRFI38_",
                "srfi38_func_info_table",
                ["operations-srfi38.c"])

# SRFI-60
build_functable("_SRFI60_",
                "srfi60_func_info_table",
                ["operations-srfi60.c"])

# SIOD
build_functable("",
                "siod_func_info_table",
                ["operations-siod.c"])

# Footer
print_footer

##########################################################

build_orig_info

# check by key
$orig_info.keys.each { |key|
  orig_regfunc = $orig_info[key]
  decl_regfunc = $declare_info[key]

  if (orig_regfunc != decl_regfunc)
    p key
    p orig_regfunc
    p decl_regfunc
  end
}

# check by key
# orig_info2.keys.each { |key|
#  orig_func = $orig_info2[key]
#  decl_func = $declare_info2[key]
#
#  if (orig_func != decl_func)
#    p orig_func
#  end
#}
